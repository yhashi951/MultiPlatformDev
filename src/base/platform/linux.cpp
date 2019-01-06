
#include "platform/linux.h"
#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Base
{
namespace Platform
{
	Linux*	pLinuxInstance_ = nullptr;

	// コンストラクタ
	Linux::Linux()
	{
		if (!pLinuxInstance_)
		{
			pLinuxInstance_ = this;
		}
	}

	// デストラクタ
	Linux::~Linux()
	{
		if (true)
		{
		//	Release();
		}

		if (pLinuxInstance_ == this)
		{
			pLinuxInstance_ = nullptr;
		}
	}

	static inline xcb_intern_atom_reply_t* intern_atom_helper(xcb_connection_t *conn, bool only_if_exists, const char *str)
	{
		xcb_intern_atom_cookie_t cookie = xcb_intern_atom(conn, only_if_exists, static_cast<uint16_t>(strlen(str)), str);
		return xcb_intern_atom_reply(conn, cookie, NULL);
	}

	// インスタンス作成
	bool Linux::CreateInstance(const char* name)
	{
		const xcb_setup_t* setup = nullptr;
		xcb_screen_iterator_t iter;
		int scr = 0;

		this->pConnection_ = xcb_connect(NULL, &scr);
		if (pConnection_ == NULL) {
			printf("Could not find a compatible Vulkan ICD!\n");
			fflush(stdout);
			exit(1);
		}

		setup = xcb_get_setup(pConnection_);
		iter = xcb_setup_roots_iterator(setup);
		while (scr-- > 0)
			xcb_screen_next(&iter);
		pScreen_ = iter.data;



		uint32_t value_mask, value_list[32];

		window_ = xcb_generate_id(pConnection_);

		value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
		value_list[0] = pScreen_->black_pixel;
		value_list[1] =
			XCB_EVENT_MASK_KEY_RELEASE |
			XCB_EVENT_MASK_KEY_PRESS |
			XCB_EVENT_MASK_EXPOSURE |
			XCB_EVENT_MASK_STRUCTURE_NOTIFY |
			XCB_EVENT_MASK_POINTER_MOTION |
			XCB_EVENT_MASK_BUTTON_PRESS |
			XCB_EVENT_MASK_BUTTON_RELEASE;

		if (false)//settings.fullscreen)
		{
			width_ = pScreen_->width_in_pixels;
			height_ =  pScreen_->height_in_pixels;
		}

		xcb_create_window(pConnection_,
			XCB_COPY_FROM_PARENT,
			window_, pScreen_->root,
			0, 0, width_, height_, 0,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			pScreen_->root_visual,
			value_mask, value_list);

		/* Magic code that will send notification when window is destroyed */
		xcb_intern_atom_reply_t* reply = intern_atom_helper(pConnection_, true, "WM_PROTOCOLS");
		pAtomWmDeleteWindow_ = intern_atom_helper(pConnection_, false, "WM_DELETE_WINDOW");

		xcb_change_property(pConnection_, XCB_PROP_MODE_REPLACE,
			window_, (*reply).atom, 4, 32, 1,
			&(*pAtomWmDeleteWindow_).atom);

		xcb_change_property(pConnection_, XCB_PROP_MODE_REPLACE,
			window_, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
			static_cast<uint32_t>(strlen(name)), name);

		free(reply);

		if (false)//settings.fullscreen)
		{
			xcb_intern_atom_reply_t *atom_wm_state = intern_atom_helper(pConnection_, false, "_NET_WM_STATE");
			xcb_intern_atom_reply_t *atom_wm_fullscreen = intern_atom_helper(pConnection_, false, "_NET_WM_STATE_FULLSCREEN");
			xcb_change_property(pConnection_,
				XCB_PROP_MODE_REPLACE,
				window_, atom_wm_state->atom,
				XCB_ATOM_ATOM, 32, 1,
				&(atom_wm_fullscreen->atom));
			free(atom_wm_fullscreen);
			free(atom_wm_state);
		}

		xcb_map_window(pConnection_, window_);


		return true;
	}

	// 更新
	bool Linux::Update()
	{
		//auto tStart = std::chrono::high_resolution_clock::now();
		//if (viewUpdated)
		//{
		//	viewUpdated = false;
		//	viewChanged();
		//}
		xcb_generic_event_t *event;
		while ((event = xcb_poll_for_event(pConnection_)))
		{
			HandleEvent(event);
			free(event);
		}

		return quit_;
	}

	// 解放
	void Linux::Release()
	{
		xcb_destroy_window(pConnection_, window_);
		xcb_disconnect(pConnection_);
	}

	// インスタンス取得
	const Linux* Linux::GetInstance()
	{
		return pLinuxInstance_;
	}

	void Linux::HandleEvent(const xcb_generic_event_t *event)
	{
		switch (event->response_type & 0x7f)
		{
		case XCB_CLIENT_MESSAGE:
			if ((*(xcb_client_message_event_t*)event).data.data32[0] == (*pAtomWmDeleteWindow_).atom)
			{
				quit_ = true;
			}
			break;
		case XCB_MOTION_NOTIFY:
		{
		//	xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;
		//	handleMouseMove((int32_t)motion->event_x, (int32_t)motion->event_y);
			break;
		}
		break;
		case XCB_BUTTON_PRESS:
		{
			//xcb_button_press_event_t *press = (xcb_button_press_event_t *)event;
			//if (press->detail == XCB_BUTTON_INDEX_1)
			//	mouseButtons.left = true;
			//if (press->detail == XCB_BUTTON_INDEX_2)
			//	mouseButtons.middle = true;
			//if (press->detail == XCB_BUTTON_INDEX_3)
			//	mouseButtons.right = true;
		}
		break;
		case XCB_BUTTON_RELEASE:
		{
			//xcb_button_press_event_t *press = (xcb_button_press_event_t *)event;
			//if (press->detail == XCB_BUTTON_INDEX_1)
			//	mouseButtons.left = false;
			//if (press->detail == XCB_BUTTON_INDEX_2)
			//	mouseButtons.middle = false;
			//if (press->detail == XCB_BUTTON_INDEX_3)
			//	mouseButtons.right = false;
		}
		break;
		case XCB_KEY_PRESS:
		{
			//const xcb_key_release_event_t *keyEvent = (const xcb_key_release_event_t *)event;
			//switch (keyEvent->detail)
			//{
			//case KEY_W:
			//	camera.keys.up = true;
			//	break;
			//case KEY_S:
			//	camera.keys.down = true;
			//	break;
			//case KEY_A:
			//	camera.keys.left = true;
			//	break;
			//case KEY_D:
			//	camera.keys.right = true;
			//	break;
			//case KEY_P:
			//	paused = !paused;
			//	break;
			//case KEY_F1:
			//	if (settings.overlay) {
			//		settings.overlay = !settings.overlay;
			//	}
			//	break;
			//}
		}
		break;
		case XCB_KEY_RELEASE:
		{
			//const xcb_key_release_event_t *keyEvent = (const xcb_key_release_event_t *)event;
			//switch (keyEvent->detail)
			//{
			//case KEY_W:
			//	camera.keys.up = false;
			//	break;
			//case KEY_S:
			//	camera.keys.down = false;
			//	break;
			//case KEY_A:
			//	camera.keys.left = false;
			//	break;
			//case KEY_D:
			//	camera.keys.right = false;
			//	break;
			//case KEY_ESCAPE:
			//	quit = true;
			//	break;
			//}
			//keyPressed(keyEvent->detail);
		}
		break;
		case XCB_DESTROY_NOTIFY:
			quit_ = true;
			break;
		case XCB_CONFIGURE_NOTIFY:
		{
			//const xcb_configure_notify_event_t *cfgEvent = (const xcb_configure_notify_event_t *)event;
			//if ((prepared) && ((cfgEvent->width != width) || (cfgEvent->height != height)))
			//{
			//	destWidth = cfgEvent->width;
			//	destHeight = cfgEvent->height;
			//	if ((destWidth > 0) && (destHeight > 0))
			//	{
			//		windowResize();
			//	}
			//}
		}
		break;
		default:
			break;
		}
	}

};	// Platform
};	// Base
