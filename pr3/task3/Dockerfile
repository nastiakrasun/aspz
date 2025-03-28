FROM gcc:latest

WORKDIR /app

COPY dice_simulator.c /app/
RUN gcc dice_simulator.c -o dice_simulator

CMD ["./dice_simulator"]
