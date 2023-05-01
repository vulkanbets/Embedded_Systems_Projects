
`timescale 1ns / 1ns


module spi_master
(
  input wire clk,
  input wire transmit,
  output reg SCK,
  output reg CS
);

// Parameters
parameter IDLE  = 2'b00;
parameter SEND  = 2'b01;
parameter DELAY = 2'b11;
parameter RECV  = 2'b10;

// State variables
reg [1:0] current_state = IDLE;
reg [1:0] next_state = IDLE;

// Counter variable to send 8-bits
reg [2:0] send_recv_counter = 3'b111;

// Counter variable for delay between SEND & RECV states
reg [2:0] delay_counter = 2;

// Delay CS line by 1 clock cycle
reg CS_Delay = 1;


// State Register
always @ (posedge clk)
begin
    if (current_state == IDLE) begin
      send_recv_counter <= 3'b111;
      current_state <= next_state;
      if (CS_Delay == 0) begin
        CS_Delay <= 1;
      end
    end
    else if (current_state == DELAY) begin
      if (delay_counter != 0) begin
        delay_counter <= delay_counter - 1;
        current_state <= current_state;
      end
      else begin
        delay_counter <= 2;
        current_state <= next_state;
      end
    end
    else begin
      if (send_recv_counter != 0) begin
        send_recv_counter <= send_recv_counter - 1;
        current_state <= current_state;
      end
      else begin
        send_recv_counter <= 3'b111;
        current_state <= next_state;
      end
      CS_Delay <= 0;
      delay_counter <= 2;
    end
end


// Next State Logic Function
always @ (*)
begin
  case (current_state)

    // IDLE state next state logic
    IDLE: begin
      if (transmit == 1) begin
        next_state <= SEND;
      end
      else begin
        next_state <= IDLE;
      end
    end

    // SEND state next state logic
    SEND: begin
      next_state <= DELAY;
    end

    // DELAY state next state logic
    DELAY: begin
      next_state <= RECV;
    end

    // RECV state next state logic
    RECV: begin
      next_state <= IDLE;
    end
    
    // <-- Default state is IDLE (HIGH)
    default: next_state <= IDLE;
    
  endcase
end


// Output Logic for Moore (FSM) Machine. Output depends only on current state
always @ (*)
begin
  case (current_state)

    IDLE: begin
      if (CS_Delay == 1) begin
        CS <= 1;
      end
      SCK <= 1;
    end

    SEND: begin
      CS <= 0;
      SCK <= clk;
    end

    DELAY: begin
      CS <= 0;
      SCK <= 1;
    end

    RECV: begin
      CS <= 0;
      SCK <= clk;
    end

    default: begin
      CS <= 1;
      SCK <= 1;
    end

  endcase
end


endmodule
