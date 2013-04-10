#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <json.h>

#include "pubnub.h"
#include "pubnub-sync.h"

int
main(void)
{
	struct pubnub_sync *sync = pubnub_sync_init();
	struct pubnub *p = pubnub_init(
			/* publish_key */ "demo",
			/* subscribe_key */ "demo",
			/* secret_key for signing */ NULL,
			/* cipher_key for encryption */ NULL,
			/* origin, by default pubsub.pubnub.com" */ NULL,
			/* pubnub_callbacks */ &pubnub_sync_callbacks,
			/* pubnub_callbacks data */ sync);
	json_object *msg;


	pubnub_here_now(
			/* struct pubnub */ p,
			/* channel */ "my_channel",
			/* timeout */ 0,
			/* callback; sync needs NULL! */ NULL,
			/* callback data */ NULL);

	if (pubnub_sync_last_result(sync) != PNR_OK) {
		msg = pubnub_sync_last_response(sync);
		fprintf(stderr, "pubnub here_now error: %d [%s]\n",
			pubnub_sync_last_result(sync), json_object_get_string(msg));
		json_object_put(msg);
		return EXIT_FAILURE;
	}

	msg = pubnub_sync_last_response(sync);
	printf("%s\n", json_object_get_string(msg));
	json_object_put(msg);


	pubnub_done(p);
	return EXIT_SUCCESS;
}
