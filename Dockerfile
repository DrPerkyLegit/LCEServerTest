FROM scottyhardy/docker-wine:latest

ENV XDG_RUNTIME_DIR=/tmp
ENV DISPLAY=:0

WORKDIR /app

COPY . .

ENTRYPOINT ["/bin/bash", "-c", "echo Container started; ls -la; /usr/bin/docker-wine ./server.exe"]