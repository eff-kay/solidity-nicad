import random
import time
from bs4 import BeautifulSoup
import requests
import os
from contract_addresses import contract_addresses

url = "https://etherscan.io/contractsVerified/"
headers = {
    'Postman-Token': "77ace3c7-dce1-6c25-d437-f00b6949a0a9",
	'cookie': '__cfduid=d95f5157eb667a7b73a7b1b9b82173e301595182803; ASP.NET_SessionId=4en4xjuteftxbzfv2dulsuww; _ga=GA1.2.1975091182.1595182808; _gid=GA1.2.1096663504.1596230286',
	'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.116 Safari/537.36'
    }

def get_html(page_url):
	querystring = {"ps":"100"}
	response = requests.request("GET", page_url, params=querystring)
	return response.text
 

def get_contract_addresses():
	contract_addresses=[]
	for i in range(1,6):
		page_url = url+str(i)
		print("getting data for ", page_url)
		source = get_html(page_url)

		soup= BeautifulSoup(source)
		table = soup.find('table')
		curr_table_data = [(row("td")[0].text.strip(), row("td")[1].text.strip()) for row in BeautifulSoup(str(table))("tr")[1:]]
		contract_addresses+=curr_table_data
		print(contract_addresses, len(contract_addresses))
	# curr_table_data = [[cell.text.strip() for cell in row("td") if cell.text.strip()] for row in BeautifulSoup(str(table))("tr")]
	return contract_addresses


def get_code(contract_address):
	code_url = "https://etherscan.io/address/{}#code".format(contract_address)
	print("getting code from url {}".format(code_url))
	response = requests.request("GET", code_url, headers=headers)
	source = response.text
	soup = BeautifulSoup(source)
	#print(soup)
	code = soup.find("pre", {"id": "editor"}).text.strip()
	print("code fetched")
	return code


def save_code_to_file(code, contract_name, address):
	file_name = "smart_contracts/"+contract_name+"_"+address+".sol"
	print("creating file with filename {}".format(file_name))
	os.makedirs(os.path.dirname(file_name),exist_ok=True)
	with open(file_name, "w") as f:
		f.write(code)
		print("file {} created".format(contract_name))


def get_all_smart_contracts(contract_address):
	count=496
	for contract_address,contract_name in contract_addresses[496:]:
		try:
			code = get_code(contract_address)
		except:
			secs = random.randrange(5,10)
			print(f'error occured,sleeping for {secs} secs')
			time.sleep(secs)
			code = get_code(contract_address)
		save_code_to_file(code, contract_name, contract_address)
		print("contract number {} fetched".format(count))
		count+=1

if __name__ == '__main__':
	get_all_smart_contracts(contract_addresses)
	#print(get_code('0x37f4ade226a15858d9eee4bb4cbc1e70ccaf290d'))
	print("done")
