
`timescale 1ns / 1ns


module spi_controller
(
    input clk,  // <-- 5 MHz (Set by CLK_WIZ)
    output reg trasnmit
);

// Initialize Nets
initial trasnmit = 0;
reg [22:0] clk_counter = 0;
reg [5:0] trasnmit_timer = 0;

always @ (posedge clk)
begin
  if(clk_counter < 225) begin
    trasnmit <= 0;
    clk_counter <= clk_counter + 1;
  end
  else begin
    if(trasnmit_timer < 2) begin
      trasnmit <= 1;
      trasnmit_timer <= trasnmit_timer + 1;
    end
    else begin
      trasnmit <= 0;
      clk_counter <= 0;
      trasnmit_timer <= 0;
    end
  end
end


endmodule
