terraform {
  backend "remote" {
    organization = "your-terraform-cloud-org"
    workspaces {
      name = "your-workspace-name"
    }
  }
}

# Add your actual infrastructure resources here
resource "null_resource" "example" {
  triggers = {
    timestamp = timestamp()
  }
}
