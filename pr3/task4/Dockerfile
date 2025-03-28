FROM gcc:latest

WORKDIR /app

COPY lottery_simulator.c /app/
RUN gcc lottery_simulator.c -o lottery_simulator

CMD ["./lottery_simulator"]
