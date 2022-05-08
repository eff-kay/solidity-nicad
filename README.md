## Solidity-NiCad:

This copy of the NiCad clone detector provides support for solidity parsing, code extracting and normalizing. All of the relevant files have been merged upstream and are part of the official NiCad (v6.2 onwards).
The latest release of NiCad can be found at https://www.txl.ca/txl-nicaddownload.html

The solidity grammar along with the relevant license can be found in the [txl/sol.grm](https://github.com/eff-kay/nicad6/blob/master/txl/sol.grm) file.
The relevant solidity normalizers/extractors can be found at [txl/sol\*.txl](https://github.com/eff-kay/nicad6/tree/master/txl).

The grammar and normalizers have been validated against a large corpus of 33,073 smart contracts extracted from Etherscan.io. This is the same corpus used in [_Code cloning in smart contracts: a case study on verified contracts from the Ethereum blockchain platform_](https://link.springer.com/article/10.1007/s10664-020-09852-5) by M. Kondo, G. Oliva, Z.M. Jiang, A. Hassan, and O. Mizuno. To get the corpus, please visit [https://github.com/SAILResearch/suppmaterial-18-masanari-smart_contract_cloning](https://github.com/SAILResearch/suppmaterial-18-masanari-smart_contract_cloning).

## Script

1. Simply run `./clone_runner.sh`. It will validate whether the code works or not. Alternatively read it to understand the steps involved in actually conducting the anlysis. This should print a latex table with the actual results

#### Steps

1. Make sure you have Txl downloaded and added to path. You can find the latest version at [this](https://www.txl.ca/txl-download.html) link.

2. Make sure you run `make` command at the root of your project. This makes sure that the grammars are compiled correctly.

3. Create a folder at the root named `systems/source-code`. Copy your corpus of smart contracts to this systems folder. At the end of this step the root should contain `systems/source-code/\*.sol` (where \*.sol represents all of the smart contracts)

4. All of the important scripts are in the `python_scripts` folder. The main scripts that creates functional clones is `create_clone_df.py`, whereas `create_contracts_clone_df.py` creates clones at the contract level. The `data` folder and the `duplicates` folder contains the results of the clones.

5. To create clones, simply run `python python_scripts/create_clone_df.py` from the root of the project. If everything is succesful . You should see a latex table printed with the actual results.

## NOTE:

These changes were adopted for the study titled [code-cloning in solidity smart contracts: a replication](). The extended replication package of the paper can be found at https://github.com/david-istvan/ethereum-cloning-tse-replication-package
