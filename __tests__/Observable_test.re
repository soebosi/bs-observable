open Jest;

describe("Observable", () => {
  testAsync("subscribe", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      ignore;
    })
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe(10) |> finish
       )
    |. ignore
  );
  testAsync("forEach", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      ignore;
    })
    |. Observable.forEach((x, _) =>
         Expect.expect(x) |> Expect.toBe(10) |> finish
       )
    |> Js.Promise.then_(() => Js.Promise.resolve())
    |. ignore
  );
  testAsync("map", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      ignore;
    })
    |. Observable.map(string_of_int)
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe("10") |> finish
       )
    |. ignore
  );
  testAsync("filter", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      observer |. SubscriptionObserver.next(20);
      observer |. SubscriptionObserver.next(30);
      ignore;
    })
    |. Observable.filter(a =>
         if (a == 20) {
           true;
         } else {
           false;
         }
       )
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe(20) |> finish
       )
    |. ignore
  );
  testAsync("reduce", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      observer |. SubscriptionObserver.next(20);
      observer |. SubscriptionObserver.next(30);
      observer |. SubscriptionObserver.complete();
      ignore;
    })
    |. Observable.reduce((acc, value) => acc ++ string_of_int(value), "00")
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toBe("00102030") |> finish
       )
    |. ignore
  );
  testAsync("concat", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      observer |. SubscriptionObserver.complete();
      ignore;
    })
    |. Observable.concat([|
         Observable.make((observer: SubscriptionObserver.t(int)) => {
           observer |. SubscriptionObserver.next(20);
           observer |. SubscriptionObserver.complete();
           ignore;
         }),
         Observable.make((observer: SubscriptionObserver.t(int)) => {
           observer |. SubscriptionObserver.next(30);
           observer |. SubscriptionObserver.complete();
           ignore;
         }),
       |])
    |. Observable.reduce((acc, value) => [value, ...acc], [])
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toEqual([30, 20, 10]) |> finish
       )
    |. ignore
  );
  testAsync("flatMap", finish =>
    Observable.make((observer: SubscriptionObserver.t(int)) => {
      observer |. SubscriptionObserver.next(10);
      observer |. SubscriptionObserver.next(30);
      observer |. SubscriptionObserver.complete();
      ignore;
    })
    |. Observable.flatMap(x => [|x, x + 10|])
    |. Observable.reduce((acc, value) => [value, ...acc], [])
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toEqual([40, 30, 20, 10]) |> finish
       )
    |. ignore
  );
  testAsync("of", finish =>
    Observable.of_([|0, 1, 2, 3|])
    |. Observable.reduce((acc, value) => [value, ...acc], [])
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toEqual([3, 2, 1, 0]) |> finish
       )
    |. ignore
  );
  testAsync("from", finish =>
    Observable.from([|0, 1, 2, 3|])
    |. Observable.reduce((acc, value) => [value, ...acc], [])
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toEqual([3, 2, 1, 0]) |> finish
       )
    |. ignore
  );
  testAsync("keepMap", finish =>
    Observable.from([|0, 1, 2, 3|])
    |. Observable.keepMap(a =>
         switch (a) {
         | a when a mod 2 == 1 => Some(a)
         | _ => None
         }
       )
    |. Observable.reduce((acc, value) => [value, ...acc], [])
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toEqual([3, 1]) |> finish
       )
    |. ignore
  );
});
