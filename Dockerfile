FROM scottyhardy/docker-wine:latest

COPY . .

RUN ls -la

ENTRYPOINT ["sleep", "infinity"]