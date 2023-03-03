#pragma once
///
/// The game world manager
///


#include "Manager.h"
#include "DsrObject.h"
#include "ObjectList.h"
#include "Vector2D.h"

// Two-letter acronym for easier access to manager.
#define WM dsr::WorldManager::getInstance()

const int WORLD_HORIZONTAL_CHARS_DEFAULT = 200;
const int WORLD_VERTICAL_CHARS_DEFAULT = 44;

namespace dsr {

	class WorldManager : public Manager {

	private:
		WorldManager();                 ///< Private since a singleton.
		WorldManager(WorldManager const&);  ///< Don't allow copy.
		void operator=(WorldManager const&); ///< Don't allow assignment.
		ObjectList m_deletions;         ///< List of all Objects to delete.
		ObjectList m_updates;

	public:
		/// Get the one and only instance of the WorldManager.
		__declspec(dllexport) static WorldManager& getInstance();

		/// Startup game world (initialize everything to empty).
		/// Return 0.
		__declspec(dllexport) int startUp() override;

		__declspec(dllexport) bool isOutOfBound(Vector2D vec) const;

		/// Shutdown game world (delete all game world Objects).
		__declspec(dllexport) void shutDown() override;

		/// Add Object to world.
		/// Return 0 if ok, else -1.
		__declspec(dllexport) int insertObject(DsrObject* p_o);

		// Update the world and do stuff yadayada
		__declspec(dllexport) void update();

		/// Remove Object from world.
		/// Return 0 if ok, else -1.
		__declspec(dllexport) int removeObject(DsrObject* p_o);
		//int onEvent(const Event* p_event) const;

		/// Return list of all Objects in world.
		/// If inactive is true, include inactive Objects.
		__declspec(dllexport) ObjectList getAllObjects() const;

		__declspec(dllexport) DsrObject* getObjectById(int id);

		__declspec(dllexport) DsrObject* getObjectByName(std::string name);

		/// Indicate Object is to be deleted at end of current game loop.
		/// Return 0 if ok, else -1.
		__declspec(dllexport) int markForDelete(DsrObject* p_o);

		__declspec(dllexport) bool positionIntersect(Vector2D p1, Vector2D p2);

		__declspec(dllexport) bool boxIntersectsBox(Box A, Box B);

		//Box getWorldBox(const DsrObject* p_o);

		// Return list of Objects collided with at position `where'.
		// Collisions only with solid Objects.
		// Does not consider if p_o is solid or not.
		__declspec(dllexport) ObjectList getCollisions(DsrObject* p_o);



		//Draw all objects.
		__declspec(dllexport) void draw();

	};

} // end of namespace dsr
