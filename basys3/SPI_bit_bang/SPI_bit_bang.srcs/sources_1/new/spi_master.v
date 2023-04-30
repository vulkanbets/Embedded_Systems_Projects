
`timescale 1ns / 1ns


module spi_master
(
  input wire clk,
  input wire transmit,
  output reg SCK,
  output reg CS
);

// Parameters
parameter IDLE = 2'b00;
parameter SEND = 2'b01;
parameter RECV = 2'b10;

// State variables
reg [1:0] current_state = IDLE;
reg [1:0] next_state = IDLE;


// State Register Asynch Reset
always @(posedge clk)
begin
    current_state <= next_state;
end


// Next State Logic Function
always @ (*)
begin
  case (current_state)
    IDLE:
    begin
      if (transmit == 1) begin
        next_state <= SEND;
      end
      else begin
        next_state <= IDLE;
      end
    end

    SEND:
    begin
      next_state <= RECV;
    end

    RECV:
    begin
      next_state <= IDLE;
    end

    default: // <-- Default is IDLE (HIGH)
    begin
      next_state <= SEND;
    end
  endcase
end


// Output Logic
always @ (*)
begin
  case (current_state)

    IDLE:
    begin
      CS <= 1;
      SCK <= 1;
    end

    SEND:
    begin
      CS <= 0;
      SCK <= clk;
    end

    RECV:
    begin
      CS <= 0;
      SCK <= clk;
    end
    default:
    begin
      CS <= 1;
      SCK <= 1;
    end

  endcase
end


endmodule
