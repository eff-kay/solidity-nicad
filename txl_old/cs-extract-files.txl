% NiCad file extractor, C#
% Jim Cordy, July 2020

% NiCad tag grammar
include "nicad.grm"

% Using C# grammar
include "csharp.grm"

% Ignore BOM headers from Windows
include "bom.grm"

% Redefinitions to collect source coordinates for function definitions as parsed input,
% and to allow for XML markup of function definitions as output

redefine program
	% Input form 
	[srcfilename] [srclinenumber] 		% Keep track of starting file and line number
	[compilation_unit]
        [srcfilename] [srclinenumber] 		% Keep track of ending file and line number
    |
	% Output form 
	[not token]				% disallow output form in input parse
	[opt xml_source_coordinate]
	[compilation_unit]
	[opt end_xml_source_coordinate]
end redefine


% Main function - extract and mark up parsed input program
function main
    replace [program]
	P [program]
    by 
    	P [convertProgram]
end function

rule convertProgram
    skipping [program]
    replace [program]
	FileName [srcfilename] LineNumber [srclinenumber]
	FileContents [compilation_unit]
        EndFileName [srcfilename] EndLineNumber [srclinenumber]

    % Convert file name and line numbers to strings for XML
    construct FileNameString [stringlit]
	_ [quote FileName] 
    construct EndLineNumberString [stringlit]
	_ [quote EndLineNumber] 

    % Output is XML form with attributes indicating input source coordinates
    construct XmlHeader [xml_source_coordinate]
	'<source file=FileNameString startline="1" endline=EndLineNumberString>
    by
	XmlHeader
	FileContents [removeOptSemis] [removeEmptyStatements]
	'</source>
end rule

rule removeOptSemis
    replace [opt ';]
	';
    by
	% none
end rule

rule removeEmptyStatements
    replace [repeat declaration_or_statement+]
	';
	More [repeat declaration_or_statement+]
    by
	More
end rule
