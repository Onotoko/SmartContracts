//
// Created by Oanh Nguyen on 12/26/18.
//

#ifndef ADDRESSBOOK_ADDRESSBOOK_H
#define ADDRESSBOOK_ADDRESSBOOK_H

#include <eosiolib/eosio.hpp>

using namespace eosio;
namespace addressbook
{
    class [[eosio::contract]]addressbook :public eosio::contract
    {
    public:
        using contract::contract;
        addressbook(name receiver, name code, datastream<const char *> ds):contract(receiver, code, ds){}

        [[eosio::action]]
        void upsert(name user, std::string fristname, std::string lastname, std::string street, std::string city, std::string state);

        [[eosio::action]]
        void earse(name user);

        [[eosio::action]]
        void notify(name user, std::string msg) {
            require_auth(get_self());
            require_recipient(user);
        }

    private:
        struct [[eosio::table]] person {
            name key;
            uint64_t age;
            std::string firstname;
            std::string lastname;
            std::string street;
            std::string city;
            std::string state;

            uint64_t primary_key() const {return key.value;}

            uint64_t get_secondary_1() const {return age;}

            EOSLIB_SERIALIZE(person,(key)(firstname)(lastname)(street)(city)(state))
        };

        void send_summary(name user, std::string message) {
            action(
                    permission_level{get_self(),"active"_n},
                    get_self(),
                    "notify"_n,
                    std::make_tuple(user, name{user}.to_string() + message)
            ).send();
        };

        typedef eosio::multi_index<"people"_n, person,
                indexed_by<"byage"_n, const_mem_fun<person, uint64_t, &person::get_secondary_1>>
        >address_index;


    };

    EOSIO_DISPATCH( addressbook, (upsert)(earse)(notify))
}


#endif //ADDRESSBOOK_ADDRESSBOOK_H
