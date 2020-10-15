% NiCad function extractor, Solidity
% Faizan Khan, September 2020 

% Rev 5.10.20 JRC - Updated to NiCad 6.1

% NiCad tag grammar
include "nicad.grm"

% Using Solidity grammar
include "sol.grm"

% Ignore BOM headers from Windows
include "bom.grm"

% Redefinitions to collect source coordinates for function definitions as parsed input,
% and to allow for XML markup of function definitions as output

redefine ContractDefinition
	[ContractDeclaration]
end redefine

define ContractHeader
    [ContractKeywords] [id] [opt IsInheritenceSpecifier] 
end define

redefine ContractDeclaration
	% Input form 
	[srcfilename] [srclinenumber] 		% Keep track of starting file and line number
	[ContractHeader] 
    '{ [NL][IN]
        [ContractBody*] [EX]
        [srcfilename] [srclinenumber] 	% Keep track of ending file and line number 
    '}
    |
	% Output form 
	[not token]				% disallow output form in input parse
	[opt xml_source_coordinate]
	[ContractHeader] 
    '{ [NL][IN]
        [ContractBody*] [EX]
    '}
	[opt end_xml_source_coordinate]
end define

define program
	... 
    | 	[repeat ContractDeclaration] 
end define


% Main function - extract and mark up function definitions from parsed input program
function main
    replace [program]
        P [program]
    construct Contracts [repeat ContractDeclaration]
        _ [^ P] 
    by
        Contracts [convertContractDeclarations]
end function

rule convertContractDeclarations
    % Find each function definition and match its input source coordinates
    replace [ContractDeclaration]
	FileName [srcfilename] LineNumber [srclinenumber]
	Header [ContractHeader] 
  	'{ 
 	    Statements [ContractBody*] 
	    EndFileName [srcfilename] EndLineNumber [srclinenumber]
	'} 

    % Convert file name and line numbers to strings for XML
    construct FileNameString [stringlit]
	_ [quote FileName] 
    construct LineNumberString [stringlit]
	_ [quote LineNumber] 
    construct EndLineNumberString [stringlit]
	_ [quote EndLineNumber] 

    % Output is XML form with attributes indicating input source coordinates
    construct XmlHeader [xml_source_coordinate]
	'<source file=FileNameString startline=LineNumberString endline=EndLineNumberString>
    by
        XmlHeader
	Header 
  	'{ 
 	    Statements 
	'} 
	'</source>
end rule
