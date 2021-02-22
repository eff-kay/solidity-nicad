This is a copy of the NiCad clone detector with solidity parser, code extractors and normalizers.

The solidity grammar along with the relevant license can be found in the [txl/sol.grm](https://github.com/eff-kay/nicad6/blob/master/txl/sol.grm) file. 
The relevant solidity normalizers/extractors can be found at [txl/sol*.txl](https://github.com/eff-kay/nicad6/tree/master/txl).

The grammar and normalizers have been validated against a large corpus of 22,181 smart contracts extracted from Etherscan.io. This is the same corpus used by Gao et al. for [SmartEmbed, 2020](https://github.com/beyondacm/SmartEmbed). All of the python scripts for testing the grammar and validation of normlizers can be located at the python_scripts folder.

All of the files have been merged upstream and are part of the official NiCad (v6.2 onwards).
The latest release of NiCad can be found at https://www.txl.ca/txl-nicaddownload.html
