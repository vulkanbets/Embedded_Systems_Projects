
`timescale 1ns / 1ns


module spi_controller
(
    input clk,  // <-- 5 MHz (Set by CLK_WIZ)
    output reg trasnmit,
    output reg [7:0] byte_To_Send
);

// Initialize Nets
initial trasnmit = 0;
reg [22:0] clk_counter = 0;
reg [5:0] trasnmit_timer = 0;

reg [7:0] rom [0:3];
initial $readmemh("bytes_To_Send.mem", rom);


reg [1:0] mem_Index = 0;
initial byte_To_Send = rom[mem_Index];


always @ (posedge clk)
begin

  byte_To_Send <= rom[mem_Index];

  if(clk_counter < 100) begin
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
      mem_Index <= mem_Index + 1;
    end
  end

end


endmodule
