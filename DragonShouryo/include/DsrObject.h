#pragma once
///
/// The base game world object
///

// System includes.
#include <string>

#include "Event.h"
#include "Vector2D.h"           ///< Objects need a float location.
#include "Box.h"

namespace dsr {

	/// Max number of events Object can be interested in.
	const int MAX_OBJ_EVENTS = 100;

	/// Types of solidness of Object.
	enum Solidness {
		HARD,       ///< Object causes collisions and impedes.
		SOFT,       ///< Object causes collision, but doesn't impede.
		SPECTRAL,   ///< Object doesn't cause collisions.
	};

	class PathFind;  // Forward reference.

	class DsrObject {

	public:
		static int max_id;	        ///< Monotonically increasing identifier.

	private:
		int m_id;		        ///< Unique game engine defined identifier.
		std::string m_name = "";
		std::string m_type;	        ///< Game programmer defined type.
		bool m_is_active;             ///< If false, Object not acted upon.
		bool m_is_visible;            ///< If true, Object gets drawn.
		bool m_delete = false;
		Vector2D m_position;            ///< Position in game world.
		Vector2D m_direction;  // Direction vector.
		float m_speed;       // Object speed in direction.
		int m_altitude;
		std::string m_sprite;
		Solidness m_solidness;
		int m_colour;
		int m_sprite_mode = 0; //0 if string, 1 if GameSprite
		int m_current_frame = 0;
		bool m_visible = true;
		bool m_draw_id = false;
		Box m_box = Box(Vector2D(0, 0), 0, 0);
		void updateBox();
	public:

		/// Construct Object. 
		/// Set default parameters and add to game world (WorldManager).
		__declspec(dllexport) DsrObject();

		/// Destroy Object. 
		/// Unregister for any interested events.
		/// Remove from game world (WorldManager).
		__declspec(dllexport) virtual ~DsrObject();

		/// Set Object id.
		__declspec(dllexport) void setId(int new_id);

		/// Get Object id.
		__declspec(dllexport) int getId() const;

		/// Set type identifier of Object.
		__declspec(dllexport) void setType(std::string new_type);

		/// Get type identifier of Object.
		__declspec(dllexport) std::string getType() const;

		/// Set position of Object.
		/// Return 0 if ok, else -1.
		__declspec(dllexport) virtual int setPosition(Vector2D new_position);

		/// Get position of Object.
		__declspec(dllexport) Vector2D getPosition() const;

		// Mark object for delete
		__declspec(dllexport) void markDelete();

		//Set item colour
		__declspec(dllexport) void setColour(int colour);

		// Set speed of Object.
		__declspec(dllexport) void setSpeed(float speed);

		// Get speed of Object.
		__declspec(dllexport) float getSpeed() const;

		// Set direction of Object.
		__declspec(dllexport) void setDirection(Vector2D new_direction);

		// Get direction of Object.
		__declspec(dllexport) Vector2D getDirection() const;

		// Get velocity of Object based on direction and speed.
		__declspec(dllexport) Vector2D getVelocity() const;

		// Set velocity of Object
		__declspec(dllexport) void setVelocity(Vector2D vec);

		__declspec(dllexport) void setDrawId(bool b);

		//
		__declspec(dllexport) Box getBoundingBox();

		// Predict Object position based on speed and direction.
		// Return predicted position. 
		__declspec(dllexport) Vector2D predictPosition();

		__declspec(dllexport) void setSolidness(Solidness s);

		__declspec(dllexport) Solidness getSolidness() const;

		//Return true if HARD or SOFT
		__declspec(dllexport) bool isSolid() const;

		__declspec(dllexport) void setSprite(std::string str);
		__declspec(dllexport) std::string getSprite() const;

		__declspec(dllexport) void setAlt(int a);

		__declspec(dllexport) void setSprMode(int i);

		__declspec(dllexport) int getSprMode();

		__declspec(dllexport) void setVisibility(bool b);

		__declspec(dllexport) bool getVisibility();

		__declspec(dllexport) void setName(std::string b);

		__declspec(dllexport) std::string getName();

		__declspec(dllexport) int getAlt();

		__declspec(dllexport) virtual void draw(int alt, bool important = false);

		__declspec(dllexport) virtual void update();

		__declspec(dllexport) virtual int eventHandler(const Event* p_e);
	};

} // end of namespace df