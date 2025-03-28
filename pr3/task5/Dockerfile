FROM gcc:latest

WORKDIR /app

COPY file_copy.c /app/
RUN gcc file_copy.c -o file_copy

CMD ["./file_copy"]
