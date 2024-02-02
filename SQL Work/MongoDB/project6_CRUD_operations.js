printjson("****************************************************************");
printjson(" 1) Document insert with insertOne()");
printjson("Inserting a single document with insertOne()");
const singleDocument = {
    elevation: 7500,
    seaSurfaceTemperature: { value: 15 },
    visibility: { distance: { value: 5000 } },
    skyConditionObservation: { totalCoverage: { value: "10" } },
    sections: ["SA1", "SX2"],
    airTemperature: { value: 22 },
    pastWeatherObservationManual: [{ atmosphericCondition: { value: "5" } }],
    pressure: { value: 600 },
    wind: { speed: { rate: 8 } },
    position: { coordinates: [25, 30]}
};
printjson(db.data.insertOne(singleDocument));

printjson("****************************************************************");
printjson(" 2) Document insert with insertMany()");
printjson("Inserting multiple documents with insertMany()");
const documents = [
    {
        elevation: 9000,
        seaSurfaceTemperature: { value: 18 },
        visibility: { distance: { value: 4000 } },
        skyConditionObservation: { totalCoverage: { value: "11" } },
        sections: ["SA1", "SY2"],
        airTemperature: { value: 24 },
        pastWeatherObservationManual: [{ atmosphericCondition: { value: "6" } }],
        pressure: { value: 580 },
        wind: { speed: { rate: 6 } },
        position: { coordinates: [35, 40] }
    },
    {
        elevation: 8500,
        seaSurfaceTemperature: { value: 12 },
        visibility: { distance: { value: 6000 } },
        skyConditionObservation: { totalCoverage: { value: "12" } },
        sections: ["SA3", "SZ2"],
        airTemperature: { value: 21 },
        pastWeatherObservationManual: [{ atmosphericCondition: { value: "7" } }],
        pressure: { value: 570 },
        wind: { speed: { rate: 7 } },
        position: { coordinates: [45, 45] }
    }
];

const documents2 = [
    {
        elevation: 6080,
        seaSurfaceTemperature: { value: 11 },
        visibility: { distance: { value: 4030 } },
        skyConditionObservation: { totalCoverage: { value: "14" } },
        sections: ["SA1", "SY7"],
        airTemperature: { value: 28 },
        pastWeatherObservationManual: [{ atmosphericCondition: { value: "9" } }],
        pressure: { value: 581 },
        wind: { speed: { rate: 1.1 } },
        position: { coordinates: [31, 41] }
    },
    {
        elevation: 8070,
        seaSurfaceTemperature: { value: 14 },
        visibility: { distance: { value: 6100 } },
        skyConditionObservation: { totalCoverage: { value: "21" } },
        sections: ["SA6", "SZ1"],
        airTemperature: { value: 11 },
        pastWeatherObservationManual: [{ atmosphericCondition: { value: "7" } }],
        pressure: { value: 531 },
        wind: { speed: { rate: 11.1 } },
        position: { coordinates: [31.6, 56.7] }
    }
];
printjson(db.data.insertMany(documents));
printjson(db.data.insertMany(documents2));

printjson("****************************************************************");
printjson(" 3) Document update with updateOne()");
printjson("Updating a single document with updateOne()");
printjson(db.data.updateOne({ elevation: 7500 }, { $set: { "airTemperature.value": 23 } }));

printjson("****************************************************************");
printjson(" 4) Document update with updateOne() and $push");
printjson("Updating a single document with updateOne() and using $push");
printjson(db.data.updateOne({ elevation: 9000 }, { $push: { sections: "SZ3" } }));

printjson("****************************************************************");
printjson(" 5 and 6) Document update with updateMany()");
printjson("Updating multiple documents with updateMany()");
printjson(db.data.updateMany({ elevation: { $gt: 8000 } }, { $set: { "wind.speed.rate": 10 } }));
printjson("Updating multiple documents with updateMany() with a different criteria");
printjson(db.data.updateMany({ "seaSurfaceTemperature.value": { $gt: 10 } }, { $set: { "pressure.value": 590 } }));

printjson("****************************************************************");
printjson(" 7) Document delete with deleteOne()");
printjson("Deleting a single document with deleteOne()");
printjson(db.data.deleteOne({ elevation: 8500 }));

printjson("****************************************************************");
printjson(" 8 and 9) Document delete with deleteMany()");
printjson("Deleting multiple documents with deleteMany()");
printjson(db.data.deleteMany({ "airTemperature.value": { $lt: 22 } }));
printjson("Deleting multiple documents with deleteMany() with a different criteria");
printjson(db.data.deleteMany({ "skyConditionObservation.totalCoverage.value": "12" }));
