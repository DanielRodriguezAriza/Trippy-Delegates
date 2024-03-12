# Trippy Delegates
Some really trippy delegates implementations in C and C++ that I did for fun. This does not deserve to exist. Literally posted just because a friend asked for this, please forgive me for these crimes against humanity.

# What does this code offer
This code adds support to make simple delegates in C and C++ with their own typedef'd delegate types.

It was purely inspired by C#'s delegate system and originally made as a joke.

This code supports adding both multicast and singlecast delegates.

Singlecast delegates perform no dynamic allocations and are basically function pointers.
Multicast delegates contain a vector with a list of all the function pointers that were added to it and will iterate over all of them to invoke them.
