

library ieee;
use ieee.std_logic_1164.all;

entity find_errors is port (
    a: in bit_vector(0 to 3);
    b: out std_logic_vector(3 downto 0);
    c: in bit_vector(5 downto 0) );
end find_errors;

architecture not_good of find_errors is
begin
  my_label: process(a, c)
  begin
    if c = "111111" then
      b <= to_stdlogicvector(a);
    else
     b <= "0101";
    end if;
  end process;
end not_good;

