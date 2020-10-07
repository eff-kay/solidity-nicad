% NiCad extract functions, Ruby
% Jim Cordy, October 2018

% NiCad tag grammar
include "nicad.grm"

% Using Ruby grammar
include "ruby.grm"

% Ignore BOM headers from Windows
include "bom.grm"

% Redefinitions to collect source coordinates for function definitions as parsed input,
% and to allow for XML markup of function definitions as output

redefine method_definition
	% Input form 
	[srcfilename] [srclinenumber] 		% Keep track of starting file and line number
	[method_header]
	    [body_statement]
	    [srcfilename] [srclinenumber] 	% Keep track of ending file and line number
	'end
    |
	% Output form 
	[not token]				% disallow output form in input parse
	[opt xml_source_coordinate]
	[method_header]
	    [body_statement]
	'end
	[opt end_xml_source_coordinate]
end redefine

define method_header
	'def [singleton_dot_or_coloncolon?] [fname] [argdecl] 
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
    	Functions [removeOptTerminators]
		  [standardizeTerminators]
end function

rule convertFunctionDefinitions
    % Find each function definition and match its input source coordinates
    replace [method_definition]
	FileName [srcfilename] LineNumber [srclinenumber]
	MethodHeader [method_header]
	    Body [body_statement]
	    EndFileName [srcfilename] EndLineNumber [srclinenumber]
	'end

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
	MethodHeader
	    Body [unmarkEmbeddedFunctionDefinitions]
	'end
	'</source>
end rule

rule removeOptTerminators
    replace $ [opt terminator]
	_ [terminator]
    by
	% nada
end rule

rule standardizeTerminators
    replace $ [terminator]
	_ [terminator]
    construct Newline [newline]
	_ [parse ""]
    by
	Newline
end rule

rule unmarkEmbeddedFunctionDefinitions
    replace $ [method_definition]
	FileName [srcfilename] LineNumber [srclinenumber]
	MethodHeader [method_header]
	    Body [body_statement]
	    EndFileName [srcfilename] EndLineNumber [srclinenumber]
	'end
    by
	MethodHeader
	    Body 
	'end
end rule
