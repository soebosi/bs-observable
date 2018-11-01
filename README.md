# bs-observable

Observables for BuckleScript/ReasonML

# Usage

```ocaml
Observable.from([|0, 1, 2, 3|])
|. Observables.subscribe(x =>
     Js.log(x);
   )
|. ignore
```
