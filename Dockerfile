FROM scottyhardy/docker-wine:latest

ENV DISPLAY=:0
ENV XDG_RUNTIME_DIR=/tmp

RUN xvfb-run wineboot

ENTRYPOINT ["xvfb-run", "-a", "wine", "Minecraft.Server.exe"]