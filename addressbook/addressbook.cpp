//
// Created by Oanh Nguyen on 12/26/18.
//
#include "addressbook.hpp"

namespace addressbook
{
    void addressbook::upsert(name user,
                std::string firstname,
                std::string lastname,
                std::string street,
                std::string city,
                std::string state)
    {

        require_auth(user);
        address_index address(_code, _code.value);
        auto it = address.find(user.value);

        if(it == address.end())
        {
            address.emplace(user,[&](auto &row){
                row.key = user;
                row.firstname = firstname;
                row.lastname  = lastname;
                row.street = street;
                row.city   = city;
                row.state  = state;
            });
            send_summary(user, " successfully emplaced record to addressbook");

        }else{

            std::string changes;

            address.modify(it, user, [&](auto &row){
                row.key = user;
                row.firstname = firstname;
                row.lastname  = lastname;
                row.street = street;
                row.city   = city;
                row.state  = state;

            });
            send_summary(user, " successfully modified record to addressbook");

        }/* end else*/

    }/* end upsert(..)*/

    void addressbook::earse(name user)
    {
        require_auth(user);

        address_index  address(_self, _code.value);
        auto it = address.find(user.value);
        eosio_assert(it != address.end(), "Record does not exist");
        address.erase(it);
        send_summary(user, " successfully erased record from addressbook");
    }/* end earse(..)*/

}

