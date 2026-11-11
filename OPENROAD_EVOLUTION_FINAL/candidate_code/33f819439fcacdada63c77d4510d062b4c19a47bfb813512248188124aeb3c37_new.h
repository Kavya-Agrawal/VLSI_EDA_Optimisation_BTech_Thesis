// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54514515;
  double density_weight = 0.23036229;
  double prefix_weight = 0.30248112;
  double neighborhood_weight = 0.29987026;
  double late_weight = 0.25496671;
  double critical_weight = 0.05352804;
  unsigned budget = 7;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
