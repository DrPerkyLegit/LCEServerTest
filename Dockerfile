FROM scottyhardy/docker-wine:latest

ENV XDG_RUNTIME_DIR=/tmp

ENTRYPOINT ["docker-wine", "Minecraft.Server.exe"]