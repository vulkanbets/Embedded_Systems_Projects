`timescale 1ns / 1ps

module pmod_LED_driver
(
    input clk,
    
    output reg [7:0] led_out
);
    reg [31:0] counter = 0;
    
    always @ ( posedge clk) begin
        if ( counter >= 124999999 ) begin
            counter <= 0;
            if ( led_out == 8'b0  ) begin
                led_out[0] <= 1;
            end else begin
                led_out <= {led_out[6:0], led_out[7]};
            end
        end else begin
            counter <= counter + 1;
        end
    end
    
endmodule
