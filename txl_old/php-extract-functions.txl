% NiCad extract functions, PHP
% Jim Cordy, October 2018

% NiCad tag grammar
include "nicad.grm"

% Using PHP grammar
include "php.grm"

% Ignore BOM headers from Windows
include "bom.grm"

% Redefinitions to collect source coordinates for function definitions as parsed input,
% and to allow for XML markup of function definitions as output

define function_header
	'function [opt '&] [opt id] '( [Param,] ')         [NL]
end define

redefine FunctionDecl
	[method_definition]
end redefine

define method_definition
	% Input form 
	[srcfilename] [srclinenumber] 		% Keep track of starting file and line number
	[function_header]
	'{                            [NL][IN] 
	    [repeat TopStatement]     [EX]
	    [srcfilename] [srclinenumber] 	% Keep track of ending file and line number
	'}  [opt ';]				
    |
	% Output form 
	[not token]				% disallow output form in input parse
	[opt xml_source_coordinate]
	[function_header]
	'{                            [NL][IN] 
	    [repeat TopStatement]     [EX]
	'}  [opt ';]				
	[opt end_xml_source_coordinate]
end define

redefine program
	...
    | 	[repeat method_definition]
end redefine


% Main function - extract and mark up function definitions from parsed input program
function main
    replace [program]
	P [program]
    construct Functions [repeat method_definition]
    	_ [^ P] 			% Extract all functions from program
	  [convertFunctionDefinitions] 	% Mark up with XML
    by 
    	Functions [removeOptSemis]
	          [removeEmptyStatements]
end function

rule convertFunctionDefinitions
    % Find each function definition and match its input source coordinates
    replace [method_definition]
	FileName [srcfilename] LineNumber [srclinenumber]
	FunctionHeader [function_header]
	'{
	    FunctionBody [repeat TopStatement]
	    EndFileName [srcfilename] EndLineNumber [srclinenumber]
	'}  Semi [opt ';]

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
	FunctionHeader 
	'{
	    FunctionBody [unmarkEmbeddedFunctionDefinitions] 
	'}
	'</source>
end rule

rule unmarkEmbeddedFunctionDefinitions
    replace [method_definition]
	FileName [srcfilename] LineNumber [srclinenumber]
	FunctionHeader [function_header]
	'{
	    FunctionBody [repeat TopStatement]
	    EndFileName [srcfilename] EndLineNumber [srclinenumber]
	'}
    by
	FunctionHeader 
	'{
	    FunctionBody 
	'}
end rule

rule removeOptSemis
    replace [opt ';]
	';
    by
	% none
end rule

rule removeEmptyStatements
    replace [repeat TopStatement]
	';
	More [repeat TopStatement]
    by
	More
end rule
