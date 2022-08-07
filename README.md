## Solidity-NiCad:

This copy of the NiCad clone detector provides support for solidity parsing, code extracting and normalizing. All of the relevant files have been merged upstream and are part of the official NiCad (v6.2 onwards).
The latest release of NiCad can be found at https://www.txl.ca/txl-nicaddownload.html

The solidity grammar along with the relevant license can be found in the [txl/sol.grm](https://github.com/eff-kay/nicad6/blob/master/txl/sol.grm) file.
The relevant solidity normalizers/extractors can be found at [txl/sol\*.txl](https://github.com/eff-kay/nicad6/tree/master/txl).

The grammar and normalizers have been validated against a large corpus of 33,073 smart contracts extracted from Etherscan.io. This is the same corpus used in [_Code cloning in smart contracts: a case study on verified contracts from the Ethereum blockchain platform_](https://link.springer.com/article/10.1007/s10664-020-09852-5) by M. Kondo, G. Oliva, Z.M. Jiang, A. Hassan, and O. Mizuno. To get the corpus, please visit [https://github.com/SAILResearch/suppmaterial-18-masanari-smart_contract_cloning](https://github.com/SAILResearch/suppmaterial-18-masanari-smart_contract_cloning).

## QUICKER START

If this is your first time reading this, we recommend skipping this section and reading the following sections.

The latest image of this repository is pushed to https://hub.docker.com/repository/docker/faizank/nicad6. Just run the following commands to get the clone detection resulting artefacts from NiCad.

```
# this downloads the image
docker pull faizank/nicad6


# this runs clone detection on the corpus inside `systems/source-code` folder and generates output inside the output folder

docker run --platform linux/x86_64 -v $(pwd)/output:/nicad6/01_data -v $(pwd)/systems:/nicad6/systems faizank/nicad6

# this will drop you in a docker console with working nicad
docker run --platform linux/x86_64 -v $(pwd)/output:/nicad6/01_data -v $(pwd)/systems:/nicad6/systems  -it faizank/nicad6 bash

```

## QUICK START

If this is your first time reading this, we recommend skipping this section as well and reading the following sections.

The commands below assume that you have [docker](https://docs.docker.com/get-started/) installed.

```
git clone git@github.com:eff-kay/solidity-nicad.git
cd solidity-nicad

# this will build the docker image locally and run it, which also runs the clone detection on a sample data, and copies the results at a new folder 01_data/clonedata/raw
docker/setup

# this script will drop you into the console with nicad enabled, were you can run the nicad commands
docker/console

# once inside the container, verify that nicad works and all dependencies are correctly installed by running the following once inside the docker console
bash docker/execute_cloning
```

## SETUP

1. Clone this repository.
2. Due to the complexity of installing all dependencies, we prepared Docker containers to run this code. Therefore you need to have docker installed on your system. You can find instructions on how to install Docker in the [official](https://docs.docker.com/get-started/) docs.
3. To run nicad on your custom dataset, place the dataset inside the `systems/source-code` folder. The scripts in our containers execute nicad cloning on the dataset available in the `systems/source-code` folder. If it doesn't find the `systems` folder then it will use the sample data attached withh this repo. Detailed of the clone executeion steps can be find in the `python_scripts/create_clone_df.py` file.

   **NOTE:** At the end of this step the root should contain `systems/source-code/\*.sol` (where \*.sol represents all of the smart contracts)

4. Then simply execute `docker/setup` from the root of this repository. This script will first build the docker container. Then run it. The container first runs nicad on the dataset, and then generates assets that are easy for consumption.

   **NOTE:** At the end of this step, a new folder `01_data/clonedata/raw` should contain the assets needed for the study [clone cloning in smart contracts](https://github.com/david-istvan/ethereum-cloning-tse-replication-package)

## CONSOLE

1. You can also just play around with the nicad tool by running `docker/console` which will drop you inside a docker container that will have a working setup of nicad.

## LOCAL NICAD

1. You can also run nicad locally on your own computer.
2. You don't need to download the nicad6 because this repository contains that relevant binaries.
3. However, you do need to download TXL for nicad to work. You can find the latest version at [this](https://www.txl.ca/txl-download.html) link. Once downloaded, go to the unzipped folder and execute the `InstallTxl` script. It should copy the relevant binaries to your path.

   **NOTE:** If you are on linux, you can use the txl tar file located inside the `docker` folder in this repository.

4. Then you run `make` command at the root of your project. This makes sure that the grammars are compiled correctly.

### PYTHON_SCRIPTS

**NOTE:** If you are using the console docker container, then you will manually need to run `pip install -r requirements.txt` for the python_scripts to work.

1. The scripts inside `python_scripts` folder are for extra anlaysis of the clone artefacts generated by the nicad tool. The main scripts that creates functional clones is `create_clone_df.py`, whereas `create_contracts_clone_df.py` creates clones at the contract level. The `data` folder and the `duplicates` folder contains the results of the clones.

2. To create clones, simply run `python python_scripts/create_clone_df.py` from the root of the project. If everything is succesful . You should see a latex table printed with the actual results.

## NOTE:

These changes were adopted for the study titled [code-cloning in solidity smart contracts: a replication](). The extended replication package of the paper can be found at https://github.com/david-istvan/ethereum-cloning-tse-replication-package
