//
//  ReportFormViewController.swift
//  SmartCityReport
//
//  Created by Sarju Mulmi on 12/4/18.
//  Copyright © 2018 Sarju Mulmi. All rights reserved.
//

import UIKit
import CoreLocation
import ImageRow
import Eureka
import SwiftSpinner
import SwiftyJSON


class ReportFormViewController: FormViewController, CLLocationManagerDelegate {
    var mbe: OMCMobileBackend!
    var auth: OMCAuthorization!
    var ccClient: OMCCustomCodeClient!
    let appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    var rowItem: String = ""
    let locationManager: CLLocationManager = CLLocationManager()
    var latitude: CLLocationDegrees?
    var longitude: CLLocationDegrees?
    let litterSpecificOptions = ["Sidewalk", "Residential Property", "Park", "Private Property"]
    let animalSpecificOptions = ["Sidewalk", "Roadway", "Building"]
    let graffitiSpecificOptions = ["Building", "Mail Box", "Bus Shelter", "Metro Station", "City Signs", "Monument", "Park", "Other"]
    var options = [String]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mbe = appDelegate.myMobileBackend()
        
        auth = mbe.authorization
        
//        self.navigationItem.setHidesBackButton(true, animated:true);
        self.navigationItem.backBarButtonItem = UIBarButtonItem(title: "Back", style: .plain, target: nil, action: nil)
        self.navigationItem.title = rowItem
        
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyHundredMeters
        locationManager.requestWhenInUseAuthorization()
        locationManager.requestLocation()
        
        switch rowItem {
        case "Litter":
            options = litterSpecificOptions
        case "Rodent Sighting":
            options = animalSpecificOptions
        default:
            break
        }
        
        form +++ Section()
            <<< ImageRow("photo"){ row in
                row.title = "Upload Photo"
                row.sourceTypes = [.PhotoLibrary, .Camera]
                row.clearAction = .no
                row.add(rule: RuleRequired(msg: "Please upload photo!"))
                row.validationOptions = .validatesOnChangeAfterBlurred
            }
                .cellUpdate({ (cell, row) in
                    cell.height = {
                        return 80
                    }
                    cell.accessoryView?.frame = CGRect(x: 0, y: 5, width: 70, height: 70)
                    if !row.isValid {
                        cell.textLabel?.textColor = .red
                    }
                })
                .onRowValidationChanged({ (cell, row) in
                    let rowIndex = row.indexPath!.row
                    while row.section!.count > rowIndex + 1 && row.section?[rowIndex + 1] is LabelRow {
                        row.section?.remove(at: rowIndex + 1)
                    }
                    if !row.isValid {
                        for (index, validationMsg) in row.validationErrors.map({$0.msg}).enumerated() {
                            let labelRow = LabelRow() {
                                $0.title = validationMsg
                                $0.cell.height = { 30 }
                            }
                            row.section?.insert(labelRow, at: row.indexPath!.row + index + 1)
                        }
                    }
                })
        // call onChange() callback here to save to object storage??
        +++ Section()
            <<< LocationRow("location"){
                $0.title = "Select Location"
                $0.add(rule: RuleRequired())
                $0.validationOptions = .validatesOnChange
//                $0.value = CLLocation(latitude: latitude ?? 38.5000, longitude: -77.3000)
        }
            
        
        +++ Section()
            <<< TextAreaRow("description") {
                $0.placeholder = "Add description"
                $0.textAreaHeight = .dynamic(initialTextViewHeight: 80)
                $0.add(rule: RuleRequired(msg: "Please add description!"))
                $0.validationOptions = .validatesOnChangeAfterBlurred
        }
                .cellUpdate({ (cell, row) in
                    if !row.isValid {
                        cell.textLabel?.textColor = .red
                    }
                })
                .onRowValidationChanged({ (cell, row) in
                    let rowIndex = row.indexPath!.row
                    while row.section!.count > rowIndex + 1 && row.section?[rowIndex + 1] is LabelRow {
                        row.section?.remove(at: rowIndex + 1)
                    }
                    if !row.isValid {
                        for (index, validationMsg) in row.validationErrors.map({$0.msg}).enumerated() {
                            let labelRow = LabelRow() {
                                $0.title = validationMsg
                                $0.cell.height = { 30 }
                            }
                            row.section?.insert(labelRow, at: row.indexPath!.row + index + 1)
                        }
                    }
                })
            
            <<< PushRow<String>("specificLocation") {
                $0.hidden = Condition.function([], { (form) -> Bool in
                    return !(self.rowItem == "Litter" || self.rowItem == "Rodent Sighting")
                })
                $0.title = "Choose a specific Location"
                $0.options = options
                $0.value = options.first
                $0.selectorTitle = "Specific Location"
                }.onPresent { from, to in
                    to.dismissOnSelection = false
                    to.dismissOnChange = false
        }
            
            <<< PushRow<String>("graffittiObject") {
                $0.hidden = Condition.function([], { (form) -> Bool in
                    return !(self.rowItem == "Illegal Graffiti")
                })
                $0.title = "Choose graffiti object"
                $0.options = graffitiSpecificOptions
                $0.value = options.first
                $0.selectorTitle = "Graffiti Object"
                }.onPresent { from, to in
                    to.dismissOnSelection = false
                    to.dismissOnChange = false
            }
            
            <<< NameRow("carMakeModel") {
                $0.hidden = Condition.function([], { (form) -> Bool in
                    return !(self.rowItem == "Abandoned Vehicle")
                })
                $0.title =  "Make/Model"
        }
            <<< NameRow("carColor") {
                $0.hidden = Condition.function([], { (form) -> Bool in
                    return !(self.rowItem == "Abandoned Vehicle")
                })
                $0.title =  "Color"
        }
            <<< NameRow("carLicense") {
                $0.hidden = Condition.function([], { (form) -> Bool in
                    return !(self.rowItem == "Abandoned Vehicle")
                })
                $0.title =  "License Plate"
        }
        
        +++ Section()
            <<< TextRow("firstName") {
                $0.title = "First Name"
                $0.placeholder = "Enter your first name"
                $0.add(rule: RuleRequired(msg: "Please provide First Name!"))
                $0.validationOptions = .validatesOnChangeAfterBlurred
        }
                .cellUpdate({ (cell, row) in
                    if !row.isValid {
                        cell.textLabel?.textColor = .red
                    }
                })
                .onRowValidationChanged({ (cell, row) in
                    let rowIndex = row.indexPath!.row
                    while row.section!.count > rowIndex + 1 && row.section?[rowIndex + 1] is LabelRow {
                        row.section?.remove(at: rowIndex + 1)
                    }
                    if !row.isValid {
                        for (index, validationMsg) in row.validationErrors.map({$0.msg}).enumerated() {
                            let labelRow = LabelRow() {
                                $0.title = validationMsg
                                $0.cell.height = { 30 }
                            }
                            row.section?.insert(labelRow, at: row.indexPath!.row + index + 1)
                        }
                    }
                })
            
            <<< TextRow("lastName") {
                $0.title = "Last Name"
                $0.placeholder = "Enter your last name"
                $0.add(rule: RuleRequired(msg: "Please provide Last Name!"))
                $0.validationOptions = .validatesOnChangeAfterBlurred
        }
                .cellUpdate({ (cell, row) in
                    if !row.isValid {
                        cell.textLabel?.textColor = .red
                    }
                })
                .onRowValidationChanged({ (cell, row) in
                    let rowIndex = row.indexPath!.row
                    while row.section!.count > rowIndex + 1 && row.section?[rowIndex + 1] is LabelRow {
                        row.section?.remove(at: rowIndex + 1)
                    }
                    if !row.isValid {
                        for (index, validationMsg) in row.validationErrors.map({$0.msg}).enumerated() {
                            let labelRow = LabelRow() {
                                $0.title = validationMsg
                                $0.cell.height = { 30 }
                            }
                            row.section?.insert(labelRow, at: row.indexPath!.row + index + 1)
                        }
                    }
                })
            
            <<< EmailRow("email") {
                $0.title = "Email"
                $0.placeholder = "a@b.com"
                $0.add(rule: RuleRequired(msg: "Please provide email!"))
                $0.add(rule: RuleEmail(msg: "Invalid Email!"))
                $0.validationOptions = .validatesOnChangeAfterBlurred
        }
                .cellUpdate({ (cell, row) in
                    if !row.isValid {
                        cell.textLabel?.textColor = .red
                    }
                })
                .onRowValidationChanged({ (cell, row) in
                    let rowIndex = row.indexPath!.row
                    while row.section!.count > rowIndex + 1 && row.section?[rowIndex + 1] is LabelRow {
                        row.section?.remove(at: rowIndex + 1)
                    }
                    if !row.isValid {
                        for (index, validationMsg) in row.validationErrors.map({$0.msg}).enumerated() {
                            let labelRow = LabelRow() {
                                $0.title = validationMsg
                                $0.cell.height = { 30 }
                            }
                            row.section?.insert(labelRow, at: row.indexPath!.row + index + 1)
                        }
                    }
                })
            
            <<< PhoneRow("phone") {
                $0.title = "Phone"
                $0.placeholder = "+1 888888888"
                $0.add(rule: RuleRequired(msg: "Please provide phone number!"))
                $0.validationOptions = .validatesOnChangeAfterBlurred
        }
                .cellUpdate({ (cell, row) in
                    if !row.isValid {
                        cell.textLabel?.textColor = .red
                    }
                })
                .onRowValidationChanged({ (cell, row) in
                    let rowIndex = row.indexPath!.row
                    while row.section!.count > rowIndex + 1 && row.section?[rowIndex + 1] is LabelRow {
                        row.section?.remove(at: rowIndex + 1)
                    }
                    if !row.isValid {
                        for (index, validationMsg) in row.validationErrors.map({$0.msg}).enumerated() {
                            let labelRow = LabelRow() {
                                $0.title = validationMsg
                                $0.cell.height = { 30 }
                            }
                            row.section?.insert(labelRow, at: row.indexPath!.row + index + 1)
                        }
                    }
                })
        
        +++ Section()
            <<< SwitchRow("isPublic") {
                $0.title = "Make Request Public?"
                $0.value = false
        }

    }
    

    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let location = locations[locations.count - 1]
        latitude = location.coordinate.latitude
        longitude = location.coordinate.longitude
        if location.horizontalAccuracy > 0 {
            (form.rowBy(tag: "location") as? LocationRow)?.value = CLLocation(latitude: latitude!, longitude: longitude!)
            locationManager.stopUpdatingLocation()
            self.tableView.reloadData()
        }
//        print(self.latitude)
//        print(self.longitude)
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print(error)
    }
    
    // need to authenticate before making the api call
    // can remove this once login step in done
    func authenticate(username: String, password: String) {
        let error: NSError? = auth.authenticate(username, password: password) as NSError?
        if (error != nil) {
            print("Error: \(error!.localizedDescription)")
            let alert = UIAlertController(title: "Error!!!!!", message:error!.localizedDescription, preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        }
    }
    
    private func getStringCoordinates(coordinates: CLLocation) -> String {
        let lat = String(coordinates.coordinate.latitude)
        let long = String(coordinates.coordinate.longitude)
        return "\(lat),  \(long)"
    }
    
    private func getRequestParams(form: Form, photoUrl: String?) -> [String: Any?] {
        return [
            "category": rowItem,
            "isPublic": (form.rowBy(tag: "isPublic") as! SwitchRow).value,
            "description": (form.rowBy(tag: "description") as! TextAreaRow).value,
            "coordinates": getStringCoordinates(coordinates: (form.rowBy(tag: "location") as! LocationRow).value!),
            "photoUrl": photoUrl ?? "https://photourl.com",
            "firstName": (form.rowBy(tag: "firstName") as! TextRow).value,
            "lastName": (form.rowBy(tag: "lastName") as! TextRow).value,
            "email": (form.rowBy(tag: "email") as! EmailRow).value,
            "phone": (form.rowBy(tag: "phone") as! PhoneRow).value,
            "specificLocation": (form.rowBy(tag: "specificLocation") as! PushRow<String>).value ?? nil,
            "carMakeModel": (form.rowBy(tag: "carMakeModel") as! NameRow).value ?? nil,
            "carColor": (form.rowBy(tag: "carColor") as! NameRow).value ?? nil,
            "carLicense": (form.rowBy(tag: "carLicense") as! NameRow).value ?? nil,
            "graffittiObject":(form.rowBy(tag: "graffittiObject") as! PushRow<String>).value ?? nil
        ]
    }
    
    @IBAction func submitRequest(_ sender: UIButton) {
        self.view.endEditing(true)
        print(getStringCoordinates(coordinates: (form.rowBy(tag: "location") as! LocationRow).value!))
        let errors = form.validate()
        if errors.count > 1 {
            print("Errors: \(errors)")
            return
        }
        SwiftSpinner.show("Requesting...")
        // need to authenticate before making api call
        // can be changed after login steps are done
        self.authenticate(username: "sarju.mulmi@oracle.com", password: "!Reston2018" )
        let data = getRequestParams(form: form, photoUrl: nil) // need to get the photo to upload to OCI and get the url
        ccClient = mbe.customCodeClient
        // post call to insert new report working
        // need to get the photo to upload to OCI and get the url
        ccClient.invokeCustomRequest("SmartCityReport/postReport", method: "POST", data: data) { (error, response, responseData) in
            if (error != nil) {
                print(error?.localizedDescription as Any)
                let alert = UIAlertController(title: "Error!!!!!", message:error!.localizedDescription, preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
                self.present(alert, animated: true, completion: nil)
                return
            }
            print(JSON(responseData!))
            let alert = UIAlertController(title: "Success", message:"Report submitted!", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        }
        
        if let uploadData = (form.rowBy(tag: "photo") as! ImageRow).value!.pngData() {
            print("yaay")
        }
        SwiftSpinner.hide()
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
