% TXL Java 8 Basis Grammar
% Version 4.1, August 2018

% Copyright 2001-2018 James R. Cordy, Xinping Guo and Thomas R. Dean

% Simple null program to test the Java# grammar

% TXL Java 8# Grammar
include "java.grm"

% Ignore BOM headers from Windows
include "bom.grm"

% Just parse
function main
    replace [program] 
        P [program]
    by
	P
end function

