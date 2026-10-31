# Specification — Game Demo

> Epic: #25 · Stories: #26, #27, #28, #29
> Owner: Brandon Cole · Sprint: 2 · Status: draft

## Scope

**In scope.**
Developing a playable game demo using the custom game engine. The game will demonstrate the engine's ECS architecture, rendering capabilities, and ability to manage a large number of entities.

The game will feature a controllable player, multiple enemy types, interactive gameplay.

The game demo will also serve as a repeatable workload for evaluating engine performance, particularly when managing and processing large numbers of entities.


**Out of scope**
•	Online multiplayer or networking.
•	A large campaign, narrative system, or extensive level progression.
•	A comprehensive inventory, crafting, or quest system.
•	A full game editor or user-generated content tools.
•	Complex storylines, dialogue systems, or cinematic sequences.
•	Full commercial-game features such as monetization, downloadable content, and achievement systems.

These features are not necessary to demonstrate the engine's functionality or evaluate its performance.

## Functional requirements


| ID | Requirement | Story |
|---|---|---|
| FR-1 | The game shall implement at least three distinct enemy types with distinguishable behaviors. | #26 |
| FR-2 | When the player successfully attacks an enemy, the game shall update the enemy's health or state, removing the enemy from active gameplay when its health reaches zero. | #26, #27 |
| FR-3 | When the player collects an available item, the game shall register the collection and update the appropriate player or game state. | #27 |
| FR-4 | When the player provides movement input, the game shall update the player's position in the corresponding direction. | #28 |
| FR-5 | When the player selects a structure and provides a valid placement location, the game shall create the selected structure within the game world. | #29 |
| FR-6 | When the player attempts to place a structure in an invalid location, the game shall reject the placement. | #29 |


## Non-functional requirements

| ID | Requirement | Why it matters here |
|---|---|---|
| NFR-1 | The game shall run using the custom game engine developed for the project without relying on a separate commercial game engine. | Demonstrates the functionality of the team's engine. |
| NFR-2 | The game shall remain playable on the hardware specifications established as the project's low-end hardware target. | Demonstrates the engine's suitability for resource-constrained hardware. |
| NFR-3 | The game shall provide a repeatable gameplay scenario that can be used to evaluate performance with increasing numbers of entities. | Supports the project's ECS performance evaluation. |


## Acceptance criteria (epic level)

- [ ] A player can launch the demo using the documented instructions and enter the playable state.
- [ ] The player can control the character using the documented input scheme.
- [ ] The game displays the player and the required gameplay entities through the custom engine.
- [ ] The core gameplay loop and the agreed win or loss condition can be demonstrated.
- [ ] The demo can run the agreed benchmark at multiple configured entity counts.
- [ ] Each benchmark run records entity count, simulation update time, and frame time.
- [ ] The demo runs on the agreed reference configuration without reproducible crashes during the acceptance test.
- [ ] The demo's tests and the required repository checks pass.

## Open questions

| Question | Owner | Needed by |
|---|---|---|
| What specific behaviors will distinguish the three enemy types? | Brandon Cole | Before enemy implementation |
| What gameplay actions will the player be able to perform? | Brandon Cole | Before player implementation |
| What entity counts will be used during the game's performance testing? | Brandon Cole | Before benchmark implementation |