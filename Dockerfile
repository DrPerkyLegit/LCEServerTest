FROM scottyhardy/docker-wine:latest

ENV DISPLAY=:0
ENV XDG_RUNTIME_DIR=/tmp

WORKDIR /app

COPY . .

ENTRYPOINT ["/bin/bash", "-c", "echo Starting server; xvfb-run -a wine ./Minecraft.Server.exe"]