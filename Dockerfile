FROM scottyhardy/docker-wine:latest

WORKDIR /app

COPY data/ /app/

ENTRYPOINT ["wine", "/app/Minecraft.Server.exe"]