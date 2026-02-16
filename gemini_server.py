from jetforce import GeminiServer, StaticDirectoryApplication
import os

class PatchedStaticApp(StaticDirectoryApplication):
    def __call__(self, environ, send_status):
        # Remove port number from the requested URL
        url = environ.get("GEMINI_URL", "")
        if ":443/" in url:
            environ["GEMINI_URL"] = url.replace(":443/", "/")
        
        # Also patch SERVER_NAME
        server_name = environ.get("SERVER_NAME", "")
        if ":443" in server_name:
            environ["SERVER_NAME"] = server_name.replace(":443", "")
        
        return super().__call__(environ, send_status)

app = PatchedStaticApp(
    root_directory="/home/mage/gemini-protocol-c/gemtext",
    index_file="index.gmi"
)

if __name__ == "__main__":
    server = GeminiServer(
        app=app,
        host="127.0.0.1",
        port=1965,
        hostname="gemini.guifl.com"
    )
    print("Starting patched Jetforce server that accepts :443 requests...")
    server.run()
