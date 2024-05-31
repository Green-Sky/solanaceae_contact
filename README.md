`plant !`

provides `contact` functionallity for solanaceae code.

relies on [EnTT](https://github.com/skypjack/entt)

## Contact Implementer Notes:

When adding a new contact, make sure to check for existing contacts of the same `ID` component first and merge into it instead.

## Implementer checklist:

- Make sure there is a root node
- every node, except the root node, needs to have a parent (a tree if only going up)

