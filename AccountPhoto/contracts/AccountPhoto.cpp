#include "AccountPhoto.hpp"

namespace apsmartcontract
{
	AccountPhoto::ACTION setPhoto(name user, string photo_hash)
	{
		require_auth(user);
		photoIndex photos(_code, _code.value);

		auto it = photos.find(user);

		if(it != photos.end())
		{
			photos.modify(it, user, [&](auto &photo){
				photo.photo_hash = photo_hash;
			});

		}
		else
		{
			photos.emplace(user, [&](auto &photo){
				photo.user = user;
				photo.photo_hash = photo_hash;
			});
		}
	} /* end setPhoto(,)*/

	AccountPhoto:: ACTION getPhoto(name user)
	{
		require_auth(user);
		photoIndex photos(_code, _code.value);

		auto photo = photos.find(user);
		eosio_assert(photo != photos.end(), "Photo not found");

		print(photo->photo_hash);
	} /* end getPhoto()*/
}