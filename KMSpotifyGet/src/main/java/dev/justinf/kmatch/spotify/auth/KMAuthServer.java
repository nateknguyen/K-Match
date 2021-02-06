package dev.justinf.kmatch.spotify.auth;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import dev.justinf.kmatch.KMSpotifyGet;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class KMAuthServer {

    private static final int PORT = 3000;
    private static final String CONTEXT = "/auth";

    private final KMSpotifyGet sg;

    private HttpServer httpServer;

    public KMAuthServer(KMSpotifyGet sg) {
        this.sg = sg;
    }

    public boolean start() {
        try {
            httpServer = HttpServer.create(new InetSocketAddress(PORT), 0);
            httpServer.createContext(CONTEXT, new RequestHandler(this));
            httpServer.setExecutor(null);
            httpServer.start();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static class RequestHandler implements HttpHandler {

        private final KMAuthServer authServer;

        private RequestHandler(KMAuthServer authServer) {
            this.authServer = authServer;
        }

        @Override
        public void handle(HttpExchange t) throws IOException {
            String result = t.getRequestURI().getQuery();
            Map<String, String> params = new HashMap<>();
            for (String s : result.split("&")) {
                String[] pair = s.split("=");
                if (pair.length != 2) continue;
                params.put(pair[0], pair[1]);
            }

            String response;
            boolean success = params.containsKey("code");
            if (!success) {
                response = "Unable to obtain Spotify authentication token. Dumping response query params below:\n";
                for (Map.Entry<String, String> pair : params.entrySet()) {
                    response = response.concat(pair.getKey() + " = " + pair.getValue() + "\n");
                }
            } else {
                response = "Successfully obtained Spotify authentication code! You can return to the application.\n";
            }

            t.sendResponseHeaders(200, response.length());
            OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();

            // We're done with the auth server after one request
            try {
                authServer.httpServer.stop(0);
            } catch (Exception ignored) { }
            finally {
                if (success) {
                    authServer.sg.authSuccess(params.get("code"));
                } else {
                    authServer.sg.authFailed();
                }
            }
        }
    }
}