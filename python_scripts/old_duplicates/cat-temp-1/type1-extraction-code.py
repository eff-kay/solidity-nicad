    a='''   1. function _reAdjustDifficulty() internal 
	2. function transfer(address _to, uint256 _value)public returns (bool success) 
	3. function transferFrom(address _from, address _to, uint256 _value)public returns (bool success) 
	4. function _transfer(address sender, address recipient, uint256 amount) internal 
	5. function doAirdrop(address _participant, uint _amount) internal 
	6. function getTokens() payable canDistr  public 
	7. function transferFrom(address _from, address _to, uint256 _amount) onlyPayloadSize(3 * 32) public returns (bool success) 
	8. function callOptionalReturn(IERC20 token, bytes memory data) private 
	9. function cancelPending(bytes32 operation) public onlyAnyBeneficiary 
	10. function deleteOperation(bytes32 operation) internal 
	11. function _cancelAllPending() internal
	12. function transferBeneficiaryShipWithHowMany(address[] memory newBeneficiaries, uint256 newHowManyBeneficiariesDecide) public onlyManyBeneficiaries 
	13. function releaseAll() public returns (uint tokens) 
	14. function _burn(address account, uint256 value) internal 
	15. function transferFrom(address _from, address _to, uint256 _value) public returns (bool) 
	16. function decreaseApproval(address _spender, uint _subtractedValue) public returns (bool) 
	17. function transfer(address _to, uint256 _value) 
	18. function transferFrom(address _from, address _to, uint256 _value) returns (bool success) 
	19. function withdraw(address to) public whenNotPaused 
	20. function depositFor(address from) public 
	21. function depositForWithReferral(address from, address referrer) public 
	22. function withdraw(address to) public 
	23. function multiTransfer(address[] memory receivers, uint256[] memory amounts) public 
	24. function _burn(address account, uint256 value) internal 
	25. function transfer(address _to, uint256 _value) returns (bool success) 
	26. function transferFrom(address _from, address _to, uint256 _value) returns (bool success) 
	27. function allocateToken (address _addr, uint256 _eth) isOwner external 
	28. function Distribute(address _participant, uint _amount) onlyOwner internal 
	29. function transfer(address to, uint256 value) public returns (bool) 
	30. function transferFrom(address from, address to, uint256 value) public returns (bool) 
	31. function approveAndCall(address _spender, uint256 _value, bytes memory _extraData) public returns (bool success) 
	32. function transfer(address _to, uint _value) returns (bool) 
	33. function transfer(address _to, uint256 _value) public whenNotPaused returns (bool) 
	34. function transferFrom(address _from, address _to, uint _value) returns (bool) 
	35. function transferFrom(address _from, address _to, uint256 _value) public whenNotPaused returns (bool) 
	36. function transferFrom(address _from, address _to, uint _value) public returns (bool)
	37. function Collect(uint _am) public payable
	38. function lock(address _holder, uint256 _amount, uint256 _releaseStart, uint256 _releaseRate) public onlyOwner returns (bool)
	39. function unlock(address _holder) public onlyOwner returns (bool)
	40. function _transfer(address _from, address _to, uint _value) internal 
	41. function transferFrom(
	    address _from,
	    address _to,
	    uint256 _value
	  )
	   public
	    returns (bool)
	42. function _transfer(address _from, address _to, uint _value) internal 
	43. function transferFrom(address _from, address _to, uint _value) returns (bool success) 
	44. function setReservedTokensListMultiple(
	    address[] addrs, 
	    uint[] inTokens, 
	    uint[] inPercentageUnit, 
	    uint[] inPercentageDecimals
	  ) public canMint onlyOwner 
	45. function setReservedTokensList(address addr, uint inTokens, uint inPercentageUnit, uint inPercentageDecimals) private canMint onlyOwner 
	46. function buyTokens(address beneficiary) public nonReentrant payable     
	47. function transferFrom(address _from, address _to, uint256 _value) public returns (bool success) 
	48. function transfer(address to, uint256 value) public returns (bool) 
	49. function transferFrom(address from, address to, uint256 value) public returns (bool)
	50. function _transfer(address _from, address _to, uint _value) internal 
	51. function _checkOnERC721Received(address from, address to, uint256 tokenId, bytes memory _data)        internal returns (bool)
	52. function transferFrom(address _from, address _to, uint256 _value) public returns (bool) 
	53. function mint(uint256 _value) public returns (bool) 
	54. function okToTransferTokens(address _holder, uint256 _amountToAdd) public view returns (bool)
	55. function _transfer(address _from, address _to, uint _value) internal 
	56. function _transfer(address _from, address _to, uint _value) internal 
	57. function sendCurrentPayment() public 
	58. function withdraw(uint256 amountCent) public returns (uint256 amountWei)
	59. function transfercheck(address check) internal returns(bool) 
	60. function investInternal(address receiver, uint128 customerId) stopInEmergency private 
	61. function distributeReservedTokens(uint reservedTokensDistributionBatch) public inState(State.Success) onlyOwner stopInEmergency 
	62. function canDistributeReservedTokens() public constant returns(bool) 
	63. function withdraw(string key) public payable
	64. function _transfer(address _from, address _to, uint _value) internal 
	65. function rescueTokens(address tokenAddr, address recipient, uint256 amount) external onlyOwner
	66. function _transfer(address sender, address recipient, uint256 amount) internal 
	67. function transferFrom(address _from, address _to, uint256 _value) public returns (bool success) 
	68. function transfer(address _to, uint256 _value) public returns (bool) 
	69. function transferFrom(address _from, address _to, uint256 _value) public returns (bool success) 
	70. function transfer(address _to, uint256 _value)
	        public
	        returns (bool)
	71. function transferFrom(address _from, address _to, uint256 _value)
	        public
        returns (bool)'''
    
    # token_ids = extract_id(a)
    # pd.set_option('max_rows', 100)
    
    # token_df = pd.DataFrame([token_ids, ['Token' for _ in range(71)]])
    # token_df = token_df.T
    # pickle.dump(token_df, open('duplicates/cat-temp/cat-token-functions-type-1.p', 'wb'))
    # print(token_df)

    ####Authoization
    a='''	1. function transferOwnership(address newOwner) onlyOwner public 
	2. function approve(address _spender, uint256 _value) public returns (bool success) 
	3. function decreaseApproval(address _spender, uint _subtractedValue) public returns (bool) 
	4. function approveAndCall(address _spender, uint256 _value, bytes memory _extraData) public returns (bool success) 
	5.  function approveAndCall(address _spender, uint256 _value, bytes _extraData) public returns (bool success) 
	6. function approveAndCall(address _spender, uint256 _value, bytes _extraData) public returns (bool success)
	7. function decreaseApproval (address _spender, uint _subtractedValue) public
	returns (bool success) 
	8. function decreaseAllowance(
	        address spender,
	        uint256 subtractedValue
	    )
	    public
	    returns (bool)
	9. function _clearApproval(uint256 tokenId) private 
	10. function checkTransferAllowed (address _sender, address _receiver, uint256 _amount) public view returns (byte)
	11. function checkTransferFromAllowed (address _sender, address _receiver, uint256 _amount) public view returns (byte) 
	12. function decreaseApproval(
	    address _spender,
	    uint256 _subtractedValue
	  )
	    public
	    returns (bool)
	13. function setEarlyParticipantWhitelist(address addr, bool status, uint minCap, uint maxCap) public onlyOwner
	14. function setEarlyParticipantWhitelistMultiple(address[] addrs, bool[] statuses, uint[] minCaps, uint[] maxCaps) public onlyOwner
	15. function updateInheritedEarlyParticipantWhitelist(address reciever, uint tokensBought) private 
	16. function updateEarlyParticipantWhitelist(address addr, uint tokensBought) public 
	17. function isAddressWhitelisted(address addr) public constant returns(bool) 
18. function acceptOwnership() public'''

    # authorization_ids = extract_id(a)
    # authorization_df = pd.DataFrame([authorization_ids, ['Authorization' for _ in range(18)]])
    # authorization_df = authorization_df.T
    # pickle.dump(authorization_df, open('duplicates/cat-temp/cat-authorization-functions-type-1.p', 'wb'))
    # print(authorization_df)

    a='''function checkHowManyBeneficiaries(uint howMany) internal returns(bool) '''
    # save_functions(a, 1, 'Poll','duplicates/cat-temp/cat-poll-functions-type-1.p')

    a='''	1. function freezingCount(address _addr) public view returns (uint count) 
	2. function freeze(address _to, uint64 _until) internal 
	3. function releaseTimeLock(address _holder) internal returns(bool) 
	4. function _extendTime(uint256 newClosingTime) internal 
	5. function CrowdsaleExt(string _name, address _token, PricingStrategy _pricingStrategy, address _multisigWallet, uint _start, uint _end, uint _minimumFundingGoal, bool _isUpdatable, bool _isWhiteListed) 
	6. function CrowdsaleTokenExt(string _name, string _symbol, uint _initialSupply, uint _decimals, bool _mintable, uint _globalMinCap)    UpgradeableToken(msg.sender) 
	7. function setStartsAt(uint time) onlyOwner 
8. function setEndsAt(uint time) public onlyOwner'''

    # save_functions(a, 8, 'TimeConstraints','duplicates/cat-temp/cat-time-constraints-functions-type-1.p')
    file_name = 'duplicates/code-filtered/1.txt'    

    a='''	1. function finalize() public inState(State.Success) onlyOwner stopInEmergency 
2. function setFinalizeAgent(FinalizeAgent addr) public onlyOwner'''

    # save_functions(a, 2, 'Termination','duplicates/cat-temp/cat-time-termination-functions-type-1.p')

    a='''	1. function mul(uint256 a, uint256 b) internal pure returns (uint256) 
	2. function mul(uint256 a, uint256 b) internal pure returns (uint256 c) 
	3. function mul(uint256 a, uint256 b) internal pure returns (uint256) 
	4. function mul(uint256 a, uint256 b) internal pure returns (uint256) 
	5. function safeMul(uint256 a, uint256 b) internal pure returns (uint256) 
6. function mul(uint256 _a, uint256 _b) internal pure returns (uint256 c) '''

    # save_functions(a, 6, 'Math','duplicates/cat-temp/cat-math-functions-type-1.p')
    a='''	1. function Try(string _response) external payable 
	2. function Start(string _question, string _response) public payable isAdmin
	3. function assert(bool assertion) internal 
	4. function migrate() external 
	5. function () payable 
	6. function initialize(uint256 _parentBlockInterval) public initializer 
	7. function submitPeriod(
		     bytes32 _prevHash,
		     bytes32 _root)
		   public onlyOperator returns (uint256 newHeight) 
	8. function upgrade(uint256 value) public 
	9. function setUpgradeAgent(address agent) external 
	10. function () external payable
	11. function Try(string _response) external payable 
	12. function setJoinedCrowdsales(address addr) private onlyOwner    
	13. function updateJoinedCrowdsalesMultiple(address[] addrs) public onlyOwner 
	14. function setPricingStrategy(PricingStrategy _pricingStrategy) public onlyOwner 
	15. function setMultisig(address addr) public onlyOwner 
	16. function getState() public constant returns (State) 
	17. function setup_key(string key) public
	18. function update_new_hash(bytes32 new_hash) public
	19. function _emit(bytes callData, uint numTopics, bytes32 topic1, bytes32 topic2, bytes32 topic3, bytes32 topic4) external onlyTarget
	20. function() external payable'''