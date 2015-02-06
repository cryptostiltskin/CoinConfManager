Coin Conf Manager
=====================

Create / Manage .conf files for your cryptocurrency wallets with this C++/Qt interface

This tool will load all of the settings from your existing .conf file if one is found,
and allow you to edit the settings in a nicer way.

Currently supports the following wallets:
ATOMIC
Bitcoin
Dogecoin
Litecoin

Contact CryptAxe or submit a merge reqest to add more.

=====================
Created for use by the ATOMIC project to allow users to easily set RPC settings.
Also serves the purpose of allowing cryptocurrency wallets to specify required,
or suggested settings that should be placed into the configuration file when the
user first runs the wallet. As this is a widget it can also be placed inside of
any Qt layout that is inside of the wallet, allowing users to change their rpc
settings at any time from within the wallet GUI.
