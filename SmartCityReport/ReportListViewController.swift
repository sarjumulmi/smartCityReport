//
//  ViewController.swift
//  SmartCityReport
//
//  Created by Sarju Mulmi on 12/3/18.
//  Copyright © 2018 Sarju Mulmi. All rights reserved.
//

import UIKit

class ReportListViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {
    
    @IBOutlet weak var tableView: UITableView!
    var selectedRow : String?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.dataSource = self
        tableView.delegate = self
        // change nav bar colors
        let navBar = self.navigationController?.navigationBar
        navBar?.barTintColor = UIColor.yellow
        navBar?.tintColor = UIColor.black
        navBar?.isTranslucent = false
        navBar?.titleTextAttributes = [NSAttributedString.Key.foregroundColor: UIColor.black]
    }
    
    // struct to store report type and categories
    struct ReportCategory {
        let name: String
        let photo: String
        var items: [[String: String]]
    }
    // add additional report categories here, ItemId is optional and not really used elsewhere in the code
    let trashItems = [["Item": "Residential Trash", "ItemId": "1"], ["Item": "Bulk Trash", "ItemId": "2"], ["Item": "Litter", "ItemId": "3"]]
    let animalSightingItems = [["Item": "Rodent Sighting", "ItemId": "1"], ["Item": "Road Kill", "ItemId": "2"]]
    let streetItems = [["Item": "Pot Hole", "ItemId": "1"], ["Item": "Broken Street Light", "ItemId": "2"]]
    let parkingItems = [["Item": "Illegal Parking", "ItemId": "1"], ["Item": "Abandoned Vehicle", "ItemId": "2"]]
    let graffitiItems = [["Item": "Illegal Graffiti", "ItemId": "1"]]
    // define report types here
    lazy var sections = [ReportCategory(name: "Trash", photo: "trash", items: trashItems),
                ReportCategory(name: "Animal Sighting", photo: "animal", items: animalSightingItems),
                ReportCategory(name: "Streets", photo: "streets", items: streetItems),
                ReportCategory(name: "Parking", photo: "parking", items: parkingItems),
                ReportCategory(name: "Graffiti", photo: "graffiti", items: graffitiItems)]

    func numberOfSections(in tableView: UITableView) -> Int {
        return self.sections.count
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return self.sections[section].name
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 35
    }
    
    func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
        let view = UIView()
        view.backgroundColor = UIColor.init(displayP3Red: 201/255, green: 201/255, blue: 205/255, alpha: 1)
        
        let image = UIImageView(image: UIImage(named: sections[section].photo))
        image.frame = CGRect(x: 5, y: 10, width: 35, height: 35)
        view.addSubview(image)
        
        let label = UILabel()
        label.text = sections[section].name
        label.frame = CGRect(x: 50, y: 10, width: 200, height: 35)
        view.addSubview(label)
        
        return view
    }
    
    func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 55.0
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let items =  self.sections[section].items
        return items.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell  = tableView.dequeueReusableCell(withIdentifier: "reportListCellIdentifier") as! ReportListCell
        let items = self.sections[indexPath.section].items
        let item = items[indexPath.row]
        cell.label.text = item["Item"]
        let tapGesture = UITapGestureRecognizer(target: self, action: #selector(goToForm(sender:)))
        cell.addGestureRecognizer(tapGesture)
        return cell
    }
    
    @objc func goToForm(sender: UITapGestureRecognizer) {
        // pass selectedRow to ReportFormViewController
        let tapLocation = sender.location(in: self.tableView)
        let indexPath = self.tableView.indexPathForRow(at: tapLocation)
        selectedRow = self.sections[indexPath!.section].items[indexPath!.row]["Item"]
        performSegue(withIdentifier: "ReportFormView", sender: self)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if let destinationVC = segue.destination as? ReportFormViewController {
            destinationVC.rowItem = selectedRow!
        }
    }
}

