# Specification — Game Engine

> Epic: #24 · Stories: #30, #31, #32, #33
> Owner: Brandon Cole · Sprint: 2 · Status: draft

## Scope

**In scope.**
Developing a lightweight game engine designed for resource-constrained hardware. The engine will use an Entity-Component-System (ECS) architecture to manage and process game entities. It will provide a real-time rendering system using OpenGL and provide a basic visual editor for importing models, creating objects, and designing game worlds.

The engine will prioritize performance, memory efficiency, and modularity over the extensive feature set offered by general-purpose commercial game engines.


**Out of scope**
•	Advanced physics simulation beyond the requirements of the game demo.
•	Multiplayer networking and online services.
•	Advanced graphics features such as ray tracing and global illumination.
•	A complete animation authoring system.
•	A general-purpose scripting language.
•	Mobile and console platform support.
•	Full-featured asset marketplace or distribution services.

These features may be considered for future development but are not required for the initial project.

## Functional requirements

| ID | Requirement | Story |
|---|---|---|
| FR-1 | When a new entity is requested, the engine shall create and return a unique entity identifier. | #30 |
| FR-2 | When a component is assigned to or removed from an entity, the engine shall update the entity's associated component data accordingly. | #30 |
| FR-3 | When an ECS system executes, the engine shall process entities that possess the component types required by that system. | #30 |
| FR-4 | When the engine is built on a supported operating system, the build system shall produce an executable for that operating system. | #31 |
| FR-5 | When the engine initializes, the rendering system shall initialize an OpenGL rendering context using the selected supported version. | #32 |
| FR-6 | When an entity contains the required transform and rendering components, the rendering system shall use their data to display the entity in the game window. | #32 |
| FR-7 | When a user creates or imports objects in the visual editor, the editor shall allow those objects to be placed in and saved as part of a game world. | #33 |


## Non-functional requirements

| ID | Requirement | Why it matters here |
|---|---|---|
| NFR-1 | The engine shall not require graphics API features newer than the minimum OpenGL version selected by the project. | Ensures compatibility with older graphics hardware. |
| NFR-2 | The ECS shall organize component data to support efficient iteration over entities with matching component types. | Supports the project's data-oriented design and performance objectives. |
| NFR-3 | The engine shall minimize unnecessary dynamic memory allocations during regular gameplay updates. | Reduces memory-management overhead on resource-constrained hardware. |
| NFR-4 | The engine shall provide runtime performance measurements, including frame time and frame rate, using a repeatable benchmark workload. | Allows the team to evaluate ECS performance. |

## Acceptance criteria (epic level)

- [ ] Entities can be created, assigned components, queried, and removed through the engine's interface.
- [ ] Automated tests demonstrate that ECS systems process eligible entities correctly and do not process removed      entities.
- [ ] The engine runs the demo's required simulation and rendering stages in the agreed order.
- [ ] The engine builds and runs on the agreed reference configuration using the selected OpenGL version.

## Open questions

| Question | Owner | Needed by |
|---|---|---|
| What is the minimum OpenGL version the engine will support? | Brandon Cole | Before rendering implementation |
| What hardware specifications will define the low-end hardware target? | Brandon Cole | Before performance testing |
| Which ECS component storage strategy will be used (e.g., sparse sets or archetypes)? | Brandon Cole | Before ECS implementation |
| Will the visual editor be a standalone application or integrated into the game engine? | Brandon Cole | Before editor implementation |