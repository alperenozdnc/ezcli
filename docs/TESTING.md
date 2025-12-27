# testing in ezcli

there exists three axes of testing:
- memory
- integrity
- sanity

## memory:
    this can be enforced with assertions, proper memory safety precautions,
    debuggers, and address sanitizers. that's why it doesn't belong in the test
    suite, and even if it did belong, incorrect memory operations means that
    the ezcli model can't be objectively judged without undefined behaviour,
    so the next two axes would automatically render incomplete.

## integrity:
    this is enforced using a specific build of ezcli built for this exact purpose.
    in this 'test' platform of ezcli, all printing is removed and any execution/
    panicking behaviour is expressed as a signal instead and is pushed to a
    signal arena. finally, we can assert that specific code paths must be executed
    in artificially created, logically tight, axiomatic contexts.

## sanity:
    this is enforced using a 'golden reference' approach. all the binaries
    that we wish to test and the inputs we want to pass are taken from the sane
    reference, then the sanity checker feeds all of the input into these binaries
    and matches them byte by byte with the sane output.

## with these axes, we confirm

- there can be an autonomous, and stable model (memory)
- this model has a set of axioms that must never be contradicted if not
  intentionally pushing a breaking change. (integrity)
- cases that are not in the surface area of the previous two axes
  are tested using a sane reference instead. (sanity)

this just means that `memory + integrity = implicit behaviour` and `sanity = explicit behaviour`
(implicit meaning non-printing and explicit meaning printing in this instance)
