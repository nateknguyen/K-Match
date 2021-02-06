package dev.justinf.kmatch.io;

import com.wrapper.spotify.model_objects.specification.AlbumSimplified;
import com.wrapper.spotify.model_objects.specification.ArtistSimplified;
import com.wrapper.spotify.model_objects.specification.Track;
import dev.justinf.kmatch.utils.StringUtils;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class TSVWriter {

    private final Set<String> writtenAlbums;
    private final Set<String> writtenArtists;
    private final Set<String> writtenTracks;
    private final Set<String> writtenAlbumArtists;
    private final Set<String> writtenTrackArtists;

    private BufferedWriter albumWriter;
    private BufferedWriter artistWriter;
    private BufferedWriter trackWriter;
    private BufferedWriter albumArtistWriter;
    private BufferedWriter trackArtistWriter;

    private final Map<Track, Exception> errorTracks;

    public TSVWriter() {
        writtenAlbums = new HashSet<>();
        writtenArtists = new HashSet<>();
        writtenTracks = new HashSet<>();
        writtenAlbumArtists = new HashSet<>();
        writtenTrackArtists = new HashSet<>();
        errorTracks = new HashMap<>();
    }

    public void end() {
        try {
            albumWriter.close();
            artistWriter.close();
            trackWriter.close();
            albumArtistWriter.close();
            trackArtistWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Error closing file writers! Please try again.");
        }
    }

    public boolean initialize() {
        try {
            artistWriter = createFileWriter("./artists.tsv");
            albumWriter = createFileWriter("./albums.tsv");
            trackWriter = createFileWriter("./tracks.tsv");
            albumArtistWriter = createFileWriter("./album_artists.tsv");
            trackArtistWriter = createFileWriter("./track_artists.tsv");
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private BufferedWriter createFileWriter(String name) throws IOException {
        File f = new File(name);
        f.createNewFile();
        return new BufferedWriter(new OutputStreamWriter(new FileOutputStream(f), StandardCharsets.UTF_8));
    }

    public void writeTracks(Track... tracks) {
        int progress = 0;

        for (Track t : tracks) {
            progress++;
            System.out.println("Writing " + t.getId() + " - " + t.getName() + " into files. (" + progress + " / " + tracks.length + ")");
            try {
                for (ArtistSimplified ta : t.getArtists()) {
                    writeArtist(ta.getId(), ta.getName());
                    writeTrackArtist(t.getId(), ta.getId());
                }

                AlbumSimplified as = t.getAlbum();
                writeAlbum(as.getId(), as.getName(), as.getReleaseDate());

                for (ArtistSimplified aa : as.getArtists()) {
                    writeArtist(aa.getId(), aa.getName());
                    writeAlbumArtist(as.getId(), aa.getId());
                }

                writeTrack(t.getId(), t.getName(), as.getId(), t.getDurationMs(), t.getPopularity());
            } catch (Exception e) {
                errorTracks.put(t, e);
            }
        }
    }

    public void writeAlbum(String id, String name, String release) throws IOException {
        if (!writtenAlbums.add(id)) return; // If the album was already written in, get out
        writeLine(albumWriter, id + "\t" + name + "\t" + release);
    }

    public void writeArtist(String id, String name) throws IOException {
        if (!writtenArtists.add(id)) return; // If the artist was already written in, get out
        writeLine(artistWriter, id + "\t" + name);
    }

    public void writeTrack(String id, String name, String albumId, int durationMs, int popularity) throws IOException {
        if (!writtenTracks.add(id)) return; // If the track was already written in, get out
        writeLine(trackWriter, id + "\t" + name + "\t" + albumId + "\t" + durationMs + "\t" + popularity);
    }

    public void writeAlbumArtist(String albumId, String artistId) throws IOException {
        if (!writtenAlbumArtists.add(albumId + artistId)) return; // If the album artist was already written in, get out
        writeLine(albumArtistWriter, albumId + "\t" + artistId);
    }

    public void writeTrackArtist(String trackId, String artistId) throws IOException {
        if (!writtenTrackArtists.add(trackId + artistId)) return; // If the track artist was already written in, get out
        writeLine(trackArtistWriter, trackId + "\t" + artistId);
    }

    private void writeLine(BufferedWriter bw, String line) throws IOException {
        bw.write(line);
        bw.newLine();
        bw.flush();
    }

    public void printTrack(Track track) {
        System.out.println(track.getName());
        System.out.print(" - Artists: ");
        System.out.println(Arrays.asList(track.getArtists()).stream().map(ArtistSimplified::getName).collect(Collectors.joining(", ")));
        System.out.println(" - Album: " + track.getAlbum().getName());
        System.out.println(" - Release: " + track.getAlbum().getReleaseDate());
        System.out.println(" - Duration: " + StringUtils.convertMillisToTime(track.getDurationMs()));
        System.out.println(" - Popularity (0-100): " + track.getPopularity());
    }

    /* getset */
    public Map<Track, Exception> getErrorTracks() {
        return errorTracks;
    }
}