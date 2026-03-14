FROM scottyhardy/docker-wine:latest

ENV XDG_RUNTIME_DIR=/tmp
ENV DISPLAY=:0

WORKDIR /app

COPY . .

ENTRYPOINT ["/bin/bash", "-c", "echo Container started; which docker-wine; find / -name docker-wine 2>/dev/null"]