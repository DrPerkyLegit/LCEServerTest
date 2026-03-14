FROM scottyhardy/docker-wine:latest

ENTRYPOINT ["wine", "Minecraft.Server.exe"]