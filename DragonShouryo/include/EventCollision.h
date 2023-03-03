#pragma once
#include "Event.h"
#include "DsrObject.h"

namespace dsr {

	const std::string COLLISION_EVENT = "df-collision";

	class EventCollision : public Event {

	private:
		Vector2D m_pos;          ///< Where collision occurred.
		DsrObject* m_p_obj1;      ///< Object moving, causing collision.
		DsrObject* m_p_obj2;      ///< Object being collided with.

	public:
		/// Create collision event at (0,0) with o1 and o2 NULL.
		__declspec(dllexport) EventCollision();

		/// Create collision event between o1 and o2 at position p.
		/// Object o1 "caused" collision by moving into object o2.
		__declspec(dllexport) EventCollision(DsrObject* p_o1, DsrObject* p_o2, Vector2D p);

		/// Set object that caused collision.
		__declspec(dllexport) void setObject1(DsrObject* p_new_o1);

		/// Return object that caused collision.
		__declspec(dllexport) DsrObject* getObject1() const;

		/// Set object that was collided with.
		__declspec(dllexport) void setObject2(DsrObject* p_new_o2);

		/// Return object that was collided with.
		__declspec(dllexport) DsrObject* getObject2() const;

		/// Set position of collision.
		__declspec(dllexport) void setPosition(Vector2D new_pos);

		/// Return position of collision.
		__declspec(dllexport) Vector2D getPosition() const;
	};

}