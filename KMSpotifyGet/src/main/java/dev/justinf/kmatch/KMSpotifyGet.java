package dev.justinf.kmatch;

import com.wrapper.spotify.model_objects.specification.Playlist;
import com.wrapper.spotify.model_objects.specification.Track;
import dev.justinf.kmatch.io.TSVWriter;
import dev.justinf.kmatch.spotify.SpotifyAPI;
import dev.justinf.kmatch.sql.KMDatabase;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class KMSpotifyGet {

    private final List<String> ignoredWords;
    private final SpotifyAPI api;
    private KMDatabase database;
    private TSVWriter tsvWriter;
    private boolean databaseMode;

    public KMSpotifyGet() {
        ignoredWords = new ArrayList<>();
        api = new SpotifyAPI(this);
        databaseMode = false;
    }

    public void start() {
        System.out.println("K-Match \"Spotify-Get\" Utility");

        Scanner input = new Scanner(System.in);
        while (true) {
            System.out.println("Would you like to generate TSV files instead of uploading to a MySQL database? (y/n)");
            System.out.print(" > ");
            String choice = input.nextLine();
            switch (choice.toLowerCase()) {
                case "y":
                    tsvModeStart();
                    return;
                case "n":
                    databaseMode = true;
                    databaseModeStart();
                    return;
                default:
                    System.out.println("Invalid choice! Please specify 'y' or 'n'.");
                    break;
            }
        }
    }

    private void tsvModeStart() {
        System.out.println("Writing data to 5 .tsv files!");
        tsvWriter = new TSVWriter();
        if (!tsvWriter.initialize()) {
            System.out.println("Unable to initialize file writers. Please try again.");
            return;
        }
        doSpotifyAuth();
    }

    private void databaseModeStart() {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter database address: ");
        String dbAddress = input.nextLine();
        System.out.print("Enter database port: ");
        String dbPort = input.nextLine();
        System.out.print("Enter database username: ");
        String dbUser = input.nextLine();
        System.out.print("Enter database password: ");
        String dbPass = input.nextLine();

        database = new KMDatabase(this, dbAddress, dbPort, dbUser, dbPass);
        doDatabaseConnect();
        doSpotifyAuth();
    }

    private void doSpotifyAuth() {
        Scanner input = new Scanner(System.in);
        System.out.println("Enter Spotify playlist ids, separated by commas.");
        System.out.print(" > ");
        api.addPlaylistIds(input.nextLine().split(","));
        System.out.println("Enter ignored keywords, separated by commas.");
        System.out.print(" > ");
        ignoredWords.addAll(Arrays.asList(input.nextLine().split(",")));

        System.out.println("Requesting Spotify authentication token... Redirecting you to browser!");
        if (!api.requestAuthCode()) {
            System.out.println("There was an error with the authentication request process. Please try again later.");
        }
    }

    private void printInformation() {
        System.out.println("\nYour information:");
        System.out.println("Database mode?: " + databaseMode);
        if (databaseMode) {
            System.out.println("Database connection info:");
            System.out.println(" - " + database.getUser() + "@" + database.getAddress() + ":" + database.getPort());
        }

        System.out.println("Spotify Playlist IDs:");
        for (String id : api.getPlaylistIds()) {
            System.out.println(" - " + id);
        }
        System.out.println("Ignored keywords (case-insensitive):");
        for (String word : ignoredWords) {
            System.out.println(" - " + word);
        }
    }

    private void doDatabaseConnect() {
        System.out.println("Attempting connection to SQL database...");
        if (database.init()) {
            System.out.println("Successfully connected to SQL database!");
        } else {
            System.out.println("Failed to connect to database. Aborting process!");
            return;
        }

        System.out.println("Creating K-Match SQL database...");
        boolean created;
        try {
            created = database.createDatabase();
        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("There was an error creating/validating the K-Match database. Aborting process!");
            return;
        }

        if (!created) {
            boolean choiceMade = false;
            Scanner input = new Scanner(System.in);
            while (!choiceMade) {
                System.out.println("It seems a database already exists for K-Match.");
                System.out.println("Abort the database update process? (y/n)");
                System.out.println("Choosing 'n' will wipe and update the database, 'y' will terminate the program.");

                String choice = input.nextLine();
                switch (choice.toLowerCase()) {
                    case "y":
                        System.out.println("Aborting database update process.");
                        System.out.println("Goodbye! :)");
                        return;
                    case "n":
                        choiceMade = true;
                        System.out.println("Preparing database for update from Spotify...");
                        try {
                            database.validateTables();
                        } catch (SQLException e) {
                            e.printStackTrace();
                            System.out.println("There was an error preparing the database for updating. Aborting process!");
                            return;
                        }
                        System.out.println("Database successfully cleared and prepared for update!");
                        break;
                    default:
                        System.out.println("Invalid choice! Please specify 'y' or 'n'.");
                        break;
                }
            }
        }

        System.out.println("Successfully verified the K-Match database.");
    }

    public void authFailed() {
        System.out.println("Unable to get Spotify authentication token! Please try again later.");
    }

    public void authSuccess(String code) {
        boolean tokenObtained = api.getAuthToken(code);
        if (!tokenObtained) {
            System.out.println("There was an error getting the authentication token. Please try again later!");
            return;
        }

        System.out.println("Successfully obtained Spotify authentication token.");
        printInformation();
        try {
            System.out.println("\nBeginning process in 5 seconds...");
            Thread.sleep(5000);
        } catch (Exception ignored) { }

        System.out.println("Proceeding to scrape entries and write information...");
        System.out.println("\nStaging playlists:");
        for (String id : api.getPlaylistIds()) {
            System.out.println("Requesting playlist information for playlist id " + id + "...");
            Playlist playlist = api.stagePlaylist(id);
            if (playlist == null) {
                System.out.println("Error staging playlist with id " + id + "!");
            } else {
                System.out.println("Success!");
                System.out.println(" - " + playlist.getId());
                System.out.println(" - \"" + playlist.getName() + "\"");
                System.out.println(" - " + playlist.getTracks().getTotal() + " tracks (expected)");
            }
        }

        System.out.println("\nPlaylists staged. Beginning track scrape process...");
        int processed = 0;
        for (Map.Entry<String, Playlist> pair : api.getStagedPlaylists().entrySet()) {
            processed++;
            System.out.println("Scraping " + pair.getValue().getName() + " playlist!");
            List<Track> tracks = api.getEntirePlaylistTracks(pair.getKey());
            if (tracks == null) {
                System.out.println("Error obtaining tracks! Please try again.");
            } else {
                System.out.println("SCRAPE SUMMARY FOR PLAYLIST \"" + pair.getValue().getName() + "\":");
                System.out.println("Obtained " + tracks.size() + " out of " + pair.getValue().getTracks().getTotal() + " expected tracks from the playlist!");

                // Change behavior here based on database mode
                System.out.println("Beginning processing of " + tracks.size() + " tracks...");
                if (databaseMode) {
                    database.uploadTracks(tracks.toArray(new Track[0]));
                    System.out.println("Database upload completed.");
                } else {
                    tsvWriter.writeTracks(tracks.toArray(new Track[0]));
                    System.out.println("File writing completed.");
                }
            }

            if (processed < api.getStagedPlaylists().size()) {
                System.out.println("Waiting 5 seconds before scraping next playlist...\n");
                try {
                    Thread.sleep(5000);
                } catch (Exception ignored) { }
            }
        }

        complete();
    }

    private void complete() {
        System.out.println("Process complete!");
        if (databaseMode) {
            System.out.println(database.getErrorTracks().size() + " tracks had errors being uploaded to the database.");
            System.out.println("Dumping error track information below:");
            for (Map.Entry<Track, Exception> pair : database.getErrorTracks().entrySet()) {
                database.printTrack(pair.getKey());
                System.out.println(pair.getValue().getClass().getName() + ": " + pair.getValue().getMessage());
            }
        } else {
            tsvWriter.end();
            System.out.println("Successfully completed TSV file writing.");
            System.out.println(tsvWriter.getErrorTracks().size() + " tracks had errors being written to the files.");
            System.out.println("Dumping error track information below:");
            for (Map.Entry<Track, Exception> pair : tsvWriter.getErrorTracks().entrySet()) {
                tsvWriter.printTrack(pair.getKey());
                System.out.println(pair.getValue().getClass().getName() + ": " + pair.getValue().getMessage());
            }
        }
    }

    /* getset */
    public List<String> getIgnoredWords() {
        return ignoredWords;
    }
}