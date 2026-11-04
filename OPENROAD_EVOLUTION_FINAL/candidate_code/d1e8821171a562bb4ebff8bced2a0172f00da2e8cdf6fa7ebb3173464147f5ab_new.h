// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07620952;
  double density_weight = 0.44576199;
  double prefix_weight = 0.32854193;
  double neighborhood_weight = 0.27892672;
  double late_weight = 0.09057757;
  double critical_weight = 0.27523535;
  unsigned budget = 18;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
