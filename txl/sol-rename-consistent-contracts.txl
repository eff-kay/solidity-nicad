% NiCad consistent renaming - Solidity functions
% Faizan Khan, September 2020 

% Rev 5.10.20 JRC - Updated to NiCad 6.1

% NiCad tag grammar
include "nicad.grm"

% Using Solidity grammar
include "sol.grm"

define ContractHeader
    [ContractKeywords] [id] [opt IsInheritenceSpecifier] 
end define

redefine ContractDefinition
    % Input form 
    [ContractHeader] 
    '{ [NL][IN]
        [ContractBody*] [EX]
    '}
end define

define potential_clone
    [ContractDefinition]
end define

% Generic consistent renaming
include "generic-rename-consistent.rul"

% Literal renaming for Java
include "sol-rename-literals.rul"
