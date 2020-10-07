import os
import re
import pandas as pd
import pickle
def extract_id(text)->list:
    pat = r'[\d\. ]*function[ ]?([a-zA-Z0-9_ ]*?)\([\s\S]*?'
    return re.findall(pat, text, re.MULTILINE)

def save_functions(a, expected_size, type, file_name, clone_type):
    authorization_ids = extract_id(a)
    authorization_df = pd.DataFrame([authorization_ids, [type for _ in range(len(authorization_ids))]])
    authorization_df = authorization_df.T
    if type=='Helper':
        authorization_df.loc[authorization_df[0]=='', 0]='function()'
    authorization_df.columns=['function_id', 'category']
    authorization_df['type']=clone_type
    pickle.dump(authorization_df, open(file_name, 'wb'))
    print(authorization_df)

def get_type2c():
    a='''	1. function tokenLike(address _token) public
	2. function getTokens() payable canDistr  public 
	3. function callOptionalReturn(IERC20 token, bytes memory data) private 
	4. function releaseOnce() public 
	5. function transfer(address to, uint256 value) public returns (bool) 
	6. function transferFrom(address from, address to, uint256 value) public returns (bool) 
	7. function giveBountyTokens(address _newInvestor, uint256 _value) public onlyOwner 
8. function transfer(address to, uint256 value) public returns (bool) '''

    type = 'Token'
    clone_type = 'type-2c'
    save_functions(a, 8, type,'duplicates/cat-temp/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)

    a='''	1. function metaIncreaseAllowance(bytes memory _signature, uint _nonce, address _spender, uint256 _addedValue, uint _reward) public returns (bool) 
	2. function decreaseApproval(address agent, uint value) public returns (bool) 
	3. function approveAndCall (address _spender, uint256 _value, bytes _extradata) public 
		a. returns(bool success)
	4. function addressToPass(address[] memory target, bool status)
	public
	onlyOwner
	5. function allowAccess(address _address) ownership public 
	6. function removeFromSendAllowed(address _to) public onlyManager 
7. function transferOwnership(address newOwner) onlyOwner public'''

    type='Authorization'
    save_functions(a, 7, type,'duplicates/cat-temp/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)

    a='''function mul(uint256 a, uint256 b) internal pure returns (uint256) '''

    type="Math"
    save_functions(a, 1, type,'duplicates/cat-temp/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)
 
    a='''	1. function getOpenedLotteries() public view returns (uint256[] memory) 
	2. function ratesForCurrencies(bytes4[] currencyKeys)
	       public
	        view
	        returns (uint[])
3. function calledUpdate(address _oldCalled, address _newCalled) public ownerOnly'''

    type='HelperFunction'
    save_functions(a, 3, type,'duplicates/cat-temp/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)
 

    type1_dirs = os.listdir('duplicates/cat-temp/')
    dfs = [pickle.load(open('duplicates/cat-temp/'+dir, 'rb')) for dir in type1_dirs] 
    # for i in range(len(dfs)):
        # dfs[i].reset_index(drop=True, inplace=True)
    combined_df = pd.concat(dfs, ignore_index=True)
    # combined_df.reset_index(inplace=True, drop=True)
    # combined_df.columns = ['function_id', 'category', 'type']
    print(combined_df)
    pickle.dump(combined_df, open('duplicates/cat-temp/combined_type_2c.p', 'wb+'))

    print(ids)    
    print("done")



def get_type3():
    a ='''  1. function _startNewMiningEpoch() internal 
    2. function getTokens() payable canDistr  public 
    3. function transferFrom(address _from, address _to, uint256 _amount) onlyPayloadSize(3 * 32) public returns (bool success) 
    4. function _vestedAmount(IERC20 token) private view returns (uint256) 
    5. function getFreezing(address _addr, uint _index) public view returns (uint64 _release, uint _balance) 
    6. function transferFrom(address _from, address _to, uint256 _value) public returns (bool) 
    7. function transfer(address _to, uint256 _value) public returns (bool success) 
    8. function transferFrom(address _from, address _to, uint256 _value) public
        returns (bool success) 
    9. function sendTokensBySameAmount(
            ERC20Interface token, 
            address[] memory addressArray, 
            uint256 amountToEachAddress,
            uint256 totalAmount
        ) public 
    10. function transfer(address to, uint256 value) public returns (bool) 
    11. function getTokens() payable canDistr  public 
    12. function _transfer(address _from, address _to, uint _value) internal 
    13. function transfer(address _to, uint256 _value) public returns(bool)
    14. function buyToken(address _investor, uint256 _invest) canDistr public 
    15. function transferManyLands(
        uint256 estateId,
        uint256[] landIds,
        address destinatary
        )
        external
        canTransfer(estateId)
    16. function transfer(address to, uint256 value) public returns (bool) 
    17. function transferFrom(address from, address to, uint256 value) public returns (bool) 
    18. function addInvestment(address addr, uint investment) public onlyOwner returns (bool) 
    19. function balanceOfAt(address _owner, uint _blockNumber) public constant returns (uint) 
    20. function reservedOf(address account) public view returns (uint256) '''

    type = 'Token'
    clone_type = 'type-3'
    save_functions(a, 20, type,'duplicates/cat-temp-3/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)

    a='''	1. function transferOwnership(address newOwner) onlyOwner public 
    2. function approve(address _spender, uint256 _value) public returns (bool success) 
    3. function decreaseApproval(address _spender, uint _subtractedValue) public returns (bool) 
    4. function changeOwner(address newOwner) public 
    5. function disqalify(address addr) public onlyOwner returns (bool) 
    6. function transfercheck(address check) internal returns(bool) 
    7. function addManyToWhitelist(address[] _addresses) external onlyOwner '''

    type='Authorization'
    save_functions(a, 7, type,'duplicates/cat-temp-3/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)

    a='''1. function _getAvailablePoll(Poll memory poll) private view returns (uint, uint, uint) '''

    type='Poll'
    save_functions(a, 1, type,'duplicates/cat-temp-3/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)

    a='''	1. function mul(uint256 a, uint256 b) internal pure returns (uint256) 
    2. function sub(percent storage p, uint a) internal view returns (uint) 
    3. function mul(uint256 _a, uint256 _b) internal pure returns (uint256)
    4. function _multiplyDecimalRound(uint x, uint y, uint precisionUnit)
            private
            pure
        returns (uint)'''

    type="Math"
    save_functions(a, 4, type,'duplicates/cat-temp-3/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)

    a='''	1. function remainingIssuableSynths(address issuer, bytes4 currencyKey)
            public
            view
            // Don't need to check for synth existing or stale rates because maxIssuableSynths will do it for us.
        returns (uint)'''

    type='HelperFunction'
    save_functions(a, 1, type,'duplicates/cat-temp-3/cat-{}-functions-{}.p'.format(type, clone_type),clone_type)


    type1_dirs = os.listdir('duplicates/cat-temp-3/')
    dfs = [pickle.load(open('duplicates/cat-temp-3/'+dir, 'rb')) for dir in type1_dirs] 
    # for i in range(len(dfs)):
        # dfs[i].reset_index(drop=True, inplace=True)
    combined_df = pd.concat(dfs, ignore_index=True)
    # combined_df.reset_index(inplace=True, drop=True)
    # combined_df.columns = ['function_id', 'category', 'type']
    print(combined_df)
    location = 'cat-temp-3'
    type='type-3'
    pickle.dump(combined_df, open('duplicates/{}/combined_{}.p'.format(location, type), 'wb+'))

    # print(ids)    
    print("done")

def get_type3b():
    location='cat-temp-3b'
    a ='''	1. function transfer(address _to, uint256 _value) public returns (bool success) 
	2. function multiTransferSingleAmount(address[] memory receivers, uint256 amount) public 
	3. function sendTokensBySameAmount(
	        ERC20Interface token, 
	        address[] memory addressArray, 
	        uint256 amountToEachAddress,
	        uint256 totalAmount
	    ) public 
	
	4. function transfer(address to, uint256 value) public returns (bool) 
	5. function giveBountyTokens(address _newInvestor, uint256 _value) public onlyOwner
	6.  function payArbitrationFeeBySender(uint _transactionID) public payable
    7. function removeInversePricing(bytes4 currencyKey) external onlyOwner '''

    type = 'Token'
    clone_type = 'type-3b'
    save_functions(a, 7, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)

    a='''	1. function changeOwner(address _newOwner) public 
	2. function approve(address _spender, uint256 _value) public returns (bool success) 
	3. function checkIsAdmin(address addr) private view returns (bool) 
	4. function removeAdmin(address addr) private
5. function approveAndCall(address _spender, uint256 _value, bytes _extraData) public returns (bool)  '''

    type = 'Authorization'
    clone_type = 'type-3b'
    save_functions(a, 5, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)

    a='''1. function autoUnlock(address _holder) internal returns (bool) '''

    type='TimeConstraints'
    save_functions(a, 1, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)

    a='''1. function safeToNextIdx() internal'''

    type='HelperFunction'
    save_functions(a, 1, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)


    type1_dirs = os.listdir('duplicates/{}/'.format(location))
    dfs = [pickle.load(open('duplicates/{}/'.format(location)+dir, 'rb')) for dir in type1_dirs] 
    # for i in range(len(dfs)):
        # dfs[i].reset_index(drop=True, inplace=True)
    combined_df = pd.concat(dfs, ignore_index=True)
    # combined_df.reset_index(inplace=True, drop=True)
    # combined_df.columns = ['function_id', 'category', 'type']
    print(combined_df)
    pickle.dump(combined_df, open('duplicates/{}/combined_{}.p'.format(location, clone_type), 'wb+'))

    # print(ids)    
    print("done")

def get_type3c():
    location='cat-temp-3c'
    clone_type = 'type-3c'
    
    a ='''	1. function withdraw() public 
	2. function transfer(address _to, uint256 _value) public returns (bool success) 
	3. function multiTransfer(address[] memory receivers, uint256[] memory amounts) public 
	4. function transfer(address _to, uint256 _value) returns (bool success) 
	5. function checkAndCallSafeTransfer(
	    address _from,
	    address _to,
	    uint256 _tokenId,
	    bytes _data
	  )
	6. function checkinterests() public view returns(uint) 
	7. function balanceOf(address who) public view returns (uint256) 
	8. function percUp(Token storage self, uint256 i) private 
	9. function mint(address[] memory accounts, uint32[] memory amounts) public onlyMinter 
	10. function getLockedTokensInGroup_(address walletAddress, uint256 groupNumber) internal view returns (uint256 balance) 
function hasReachedSoftCap() public view returns (bool) '''

    type = 'Token'

    save_functions(a, 11, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)

    a='''	1. function changeOwner(address _newOwner) public 
	2. function clearApproval(address _owner, uint256 _tokenId) internal 
	3. function _clearApproval(uint256 tokenId) private 
	4. function checkIsAdmin(address addr) private view returns (bool) 
	5. function isAddressWhitelisted(address addr) public constant returns(bool) 
function addAddressToGovernanceContract(address addr) onlyOwner public returns(bool success) '''

    type = 'Authorization'
    save_functions(a, 6, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)

    a='''1. function timeOutBySender(uint _transactionID) public '''

    type='TimeConstraints'
    save_functions(a, 1, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)

    a='''1. function setPaused(bool value) external onlyOwner'''

    type='Termination'
    save_functions(a, 1, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)


    a='''1. function _multiplyDecimalRound(uint x, uint y, uint precisionUnit)
	        private
	        pure
        returns (uint)'''

    type='Math'
    save_functions(a, 1, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)

    a='''	1. function safeToNextIdx() internal
2. function () public payable'''

    type='HelperFunction'
    save_functions(a, 2, type,'duplicates/{}/cat-{}-functions-{}.p'.format(location, type, clone_type),clone_type)


    type1_dirs = os.listdir('duplicates/{}/'.format(location))
    dfs = [pickle.load(open('duplicates/{}/'.format(location)+dir, 'rb')) for dir in type1_dirs] 
    # for i in range(len(dfs)):
        # dfs[i].reset_index(drop=True, inplace=True)
    combined_df = pd.concat(dfs, ignore_index=True)
    # combined_df.reset_index(inplace=True, drop=True)
    # combined_df.columns = ['function_id', 'category', 'type']
    print(combined_df)
    pickle.dump(combined_df, open('duplicates/{}/combined_{}.p'.format(location, clone_type), 'wb+'))

    # print(ids)    
    print("done")


def create_dfs_from_analyzed_functions(config, type):
    cats = ["Authorization", "Token", "Poll", "Math", "Poll", "Termination", "TimeConstraints", "Helper"]

    os.makedirs('duplicates/functions-analyzed-dfs/{}'.format(type), exist_ok=True)
    for cat in cats:
        file_contents = open('analyzed-functions/{}/{}/{}'.format(config, type, cat+'.txt')).read()
        save_functions(file_contents, 11, cat,'duplicates/functions-analyzed-dfs/{}/{}.p'.format(type, cat),type)

    dfs = [pickle.load(open('duplicates/functions-analyzed-dfs/{}/{}.p'.format(type, cat), 'rb')) for cat in cats] 
    # for i in range(len(dfs)):
        # dfs[i].reset_index(drop=True, inplace=True)
    combined_df = pd.concat(dfs, ignore_index=True)
    # combined_df.reset_index(inplace=True, drop=True)
    # combined_df.columns = ['function_id', 'category', 'type']
    print(combined_df)
    pickle.dump(combined_df, open('duplicates/functions-analyzed-dfs/{}/merged_df.p'.format(type), 'wb+'))



def create_final_df(config):
    types = ['type-1', 'type-2', 'type-2c', 'type-3-1', 'type-3-2', 'type-3-2c']
    os.makedirs('duplicates/functions-analyzed-dfs', exist_ok=True)
    
    for type in types[4:]:
        create_dfs_from_analyzed_functions(config, type) 
    
    dfs = [pickle.load(open('duplicates/functions-analyzed-dfs/{}/merged_df.p'.format(type), 'rb')) for type in types[4:]]
    combined_df = pd.concat(dfs, ignore_index=True)
    print(combined_df)
    pickle.dump(combined_df, open('analyzed-functions/{}/combined-df.p'.format(config), 'wb'))

if __name__ == "__main__":
    create_dfs_from_analyzed_functions('min4', 'type-1')
    # create_final_df('min5')
    # files= ['combined_type_1.p', 'combined_type_2c.p', 'combined_type-3.p', 'combined_type-3b.p','combined_type-3c.p']   
    # dirs = ['cat-temp-1', 'cat-temp-2', 'cat-temp-3','cat-temp-3b', 'cat-temp-3c']

    # type1 =pickle.load(open('duplicates/{}/{}'.format(dirs[0], files[0]), 'rb'))
    # type1.columns = ['function_id', 'category', 'type']

    # pickle.dump(type1, open('duplicates/{}/{}'.format(dirs[0], files[0]), 'wb'))

    # dfs = [pickle.load(open('duplicates/{}/{}'.format(i, file), 'rb')) for i, file in zip(dirs, files)]
    # combined_df = pd.concat(dfs, ignore_index=True)
    # print(combined_df)
    # pickle.dump(combined_df, open('duplicates/category-count-function-ids.p', 'wb'))
