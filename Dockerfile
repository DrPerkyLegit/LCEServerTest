FROM scottyhardy/docker-wine:latest

ENTRYPOINT ["wineconsole", "--backend=curses", "Minecraft.Server.exe"]