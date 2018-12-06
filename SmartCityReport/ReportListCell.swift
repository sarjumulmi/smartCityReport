//
//  ReportListCellTableViewCell.swift
//  SmartCityReport
//
//  Created by Sarju Mulmi on 12/4/18.
//  Copyright © 2018 Sarju Mulmi. All rights reserved.
//

import UIKit

class ReportListCell: UITableViewCell {

    @IBOutlet weak var label: UILabel!
    
    
    @IBOutlet weak var rightArrowLabel: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
