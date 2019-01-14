//Refence https://github.com/zachalam/AccountPhoto/tree/master/contracts/AccountPhoto
//Create by Oanh Nguyen 11/11/2018

#ifndef ACCOUNTPHOTO_BLOCKCHAIN_H
#define ACCOUNTPHOTO_BLOCKCHAIN_H

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <string>

using namespace eosio;
using namespace std;

namespace apsmartcontract
{
	CONTRACT AccountPhoto:public contract::contract{
	private:
		TABLE photos{
			name account_name;
			string photo_hash;

			uint64_t primary_key() const {return account_name;}

			EOSLIB_SERIALIRE(photos, (account_name)(photo_hash))
		}
		typedef multi_index<N(photos), photos> photoIdex;

	public:
		using contract::contract;

		AccountPhoto(name receiver, name code, datastream<const char *> ds):contract(receiver, code, ds){}

		ACTION setPhoto(name user, string photo_hash);
		ACTION getPhoto(name user);
	}

	EOSIO_DISPATCH(AccountPhoto, (setPhoto)(getPhoto))
}

#endif //ACCOUNTPHOTO_BLOCKCHAIN_H
